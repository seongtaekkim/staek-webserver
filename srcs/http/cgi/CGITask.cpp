#include "CommonGatewayInterface.hpp"
#include "../../exception/Exception.hpp"
#include "CGITask.hpp"
#include "../response/method/Method.hpp"
#include "../HTTPState.hpp"
#include "../make/ResponseMaker.hpp"
#include "../response/HTTPState.hpp"
#include "../server/Client.hpp"
#include "../request/Request.hpp"
// #include <http/response/body/impl/CGIResponseBody.hpp>
#include "../response/Response.hpp"
#include "../server/Socket.hpp"
// #include <log/Logger.hpp>
// #include <log/LoggerFactory.hpp>
#include <sys/types.h>
#include "../../util/Base.hpp"
#include <iostream>
#include <string>

CGITask::CGITask(HTTPClient &client, CommonGatewayInterface &cgi) :
		_client(client),
		_cgi(cgi),
		_out(*FileDescriptor::create(_cgi.out())),
		wroteBodyUpTo(),
		_running(true),
		_nextCalled(false)
{
	// FileDescriptor *f = new FileDescriptor(_cgi.out());
	// if (_client.request().method().get()->hasBody())
	// 	NIOSelector::instance().add(m_cgi.in(), *this, NIOSelector::WRITE);
	// else
	// 	m_cgi.in().close();

	// NIOSelector::instance().add(m_cgi.out(), *this, NIOSelector::READ);
}

CGITask::~CGITask()
{
	_cgi.kill();

	KqueueManage::instance().delEvent(_cgi.in().getFd());
	KqueueManage::instance().delEvent(_cgi.out().getFd());

	delete &_out;
	delete &_cgi;
}

bool
CGITask::running()
{
	return (_running);
}

bool CGITask::send(FileDescriptor &fd) {
	
	if (wroteBodyUpTo == _client.body().length())
		return (true);

	ssize_t wrote = fd.write(_client.body().c_str() + wroteBodyUpTo, _client.body().length() - wroteBodyUpTo);

	if (wrote <= 0)
	{
		_cgi.in().close();
		KqueueManage::instance().delEvent(_cgi.in().getFd());
		return (true);
	}

	wroteBodyUpTo += wrote;
	if (wroteBodyUpTo == _client.body().length())
	{
		_cgi.in().close();
		KqueueManage::instance().delEvent(_cgi.in().getFd());
		return (true);
	}

	return (false);
}

bool CGITask::recv(FileDescriptor &fd) {
	(void)fd;

	ssize_t r = _out.read();
	if (r == -1)
	{
		_client.response().status(*HTTPStatus::INTERNAL_SERVER_ERROR);
		_client.filterChain().next();

		KqueueManage::instance().update(m_client.socket(), KqueueManage::WRITE);
		return (true);
	}

	if (r == 0 && _out.empty() && _parser.state() != HTTPHeaderFieldsParser::S_END)
	{
		_client.response().status(*HTTPStatus::GATEWAY_TIMEOUT);

		_nextCalled = true;
		_client.filterChain().next();
		return (true);
	}

	if (_parser.state() != HTTPHeaderFieldsParser::S_END)
	{
		char c;
		bool parsed = false;

		try
		{
			while (_out.next(c))
			{
				_parser.consume(c);

				if (m_headerFieldsParser.state() == HTTPHeaderFieldsParser::S_END)
				{
					parsed = true;
					break;
				}
			}

			if (parsed)
			{
				m_client.response().headers().merge(m_headerFieldsParser.headerFields());

				Optional<std::string> statusOpt = m_headerFieldsParser.headerFields().get(HTTPHeaderFields::STATUS);
				if (statusOpt.present())
				{
					std::string codePart = statusOpt.get().substr(0, statusOpt.get().find(' '));

					int code = Number::parse<int>(codePart);
					const HTTPStatus *newStatus = HTTPStatus::find(code);

					if (newStatus)
						m_client.response().status(*newStatus);
				}

				m_client.response().headers().chunkedTransferEncoding();
				m_client.response().body(new CGIResponseBody(m_client, *this));

				m_nextCalled = true;
				m_client.filterChain().next();

				NIOSelector::instance().update(m_client.socket(), NIOSelector::WRITE);
			}

			return (false);
		}
		catch (Exception &exception)
		{
			LOG.warn() << "CGI produced an error: " << exception.message() << std::endl;

			m_client.response().status(*HTTPStatus::INTERNAL_SERVER_ERROR);

			m_nextCalled = true;
			m_client.filterChain().next();

			NIOSelector::instance().update(m_client.socket(), NIOSelector::WRITE);
			return (true);
		}
	}

	if (m_bufferedOut.hasReadEverything())
	{
		NIOSelector::instance().remove(m_cgi.out());
		return (true);
	}

	return (false);
}

bool
CGITask::isDone()
{
	return (m_bufferedOut.hasReadEverything() && m_bufferedOut.empty());
}

bool
CGITask::hasReadHeaders()
{
	return (m_headerFieldsParser.state() != HTTPHeaderFieldsParser::S_END);
}

FileDescriptorBuffer&
CGITask::out()
{
	return (m_bufferedOut);
}

bool
CGITask::timeoutTouch()
{
	if (m_running)
	{
		m_running = m_cgi.running();

		return (true);
	}

	return (false);
}

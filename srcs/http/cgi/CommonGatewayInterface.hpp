#ifndef COMMONGATEWAYINTERFACE_HPP
#define COMMONGATEWAYINTERFACE_HPP

#include "../../config/Config.hpp"
#include "../../file/FileDescriptor.hpp"
#include <sys/types.h>
#include "../../util/SEnvironment.hpp"
#include <string>

class CGITask;

class Logger;
class FileDescriptor;
class CGIBlock;
class HTTPClient;

class CommonGatewayInterface {
	private:
		pid_t m_pid;
		FileDescriptor &m_in;
		FileDescriptor &m_out;
		bool m_killed;

	private:
		CommonGatewayInterface();
		CommonGatewayInterface(pid_t pid, FileDescriptor &in, FileDescriptor &out);
		CommonGatewayInterface(const CommonGatewayInterface &other);

		CommonGatewayInterface& operator=(const CommonGatewayInterface &other);

	public:
		virtual ~CommonGatewayInterface();

		void
		kill();

		void
		wait();

		bool
		running();

		inline FileDescriptor&
		in() const
		{
			return (m_in);
		}

		inline FileDescriptor&
		out() const
		{
			return (m_out);
		}

		inline pid_t
		pid() const
		{
			return (m_pid);
		}

	public:
		static CGITask* execute(Client& client, const CGIBlock &cgiBlock, const Environment &environment);

	public:
		static const std::string ENV_AUTH_TYPE;
		static const std::string ENV_CONTENT_LENGTH;
		static const std::string ENV_CONTENT_TYPE;
		static const std::string ENV_GATEWAY_INTERFACE;
		static const std::string ENV_PATH_INFO;
		static const std::string ENV_PATH_TRANSLATED;
		static const std::string ENV_QUERY_STRING;
		static const std::string ENV_REMOTE_ADDR;
		static const std::string ENV_REMOTE_PORT;
		static const std::string ENV_REMOTE_IDENT;
		static const std::string ENV_REMOTE_USER;
		static const std::string ENV_REQUEST_METHOD;
		static const std::string ENV_REQUEST_URI;
		static const std::string ENV_SCRIPT_FILENAME;
		static const std::string ENV_SCRIPT_NAME;
		static const std::string ENV_SERVER_NAME;
		static const std::string ENV_SERVER_PORT;
		static const std::string ENV_SERVER_PROTOCOL;
		static const std::string ENV_SERVER_SOFTWARE;
};

#endif

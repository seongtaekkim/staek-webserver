#include "Webserv.hpp"
#include "../config/block/ServerBlock.hpp"
#include "../config/Config.hpp"
#include "../iom/KqueueManage.hpp"
#include "../http/server/Server.hpp"
#include "../log/LogFactory.hpp"
#include "../util/Base.hpp"
#include "SHTTP.hpp"

Webserv::Webserv(void) {}
Webserv::Webserv(const ServerList& server) : _servers(server), _isRun(false), _isStop(false) {}

Webserv::Webserv(const Webserv& other) {
	(void)other;
}

Webserv& Webserv::operator=(const Webserv& other) {
	(void)other;
	return (*this);
}

Webserv::~Webserv(void) {}

Server& Webserv::getServer(unsigned long ident) {
	int serverFd = KqueueManage::instance().serverFd((int)ident);
	for (std::list<Server*>::iterator it = this->_servers.begin(); it != this->_servers.end(); it++) {
		if ((*it)->getSocket()->getFd() == serverFd) {
			return *(*it);
		}
	}
	return (*this->_servers.front());
}

void Webserv::run(void) {

	for (std::list<Server*>::iterator it = _servers.begin(); it != _servers.end(); it++)
		(*it)->init();
	this->_isRun = true;

    struct kevent* curr_event;
    while (this->_isRun) {
		KqueueManage::instance().kevent();
		(&KqueueManage::instance())->_changeVec.clear();
        for (int i = 0; i < KqueueManage::instance().eventCount() ; ++i) {
            curr_event = &KqueueManage::instance().eventArr()[i];
			Server& server = getServer(curr_event->ident);
			usleep(500);
			
            if (curr_event->flags & EV_ERROR) {
                if (curr_event->ident == (unsigned long)server.getSocket()->getFd())
                    throw IOException("server socket error", errno);
            }
            else if (curr_event->filter == EVFILT_READ)
            {
                if (curr_event->ident == (unsigned long)server.getSocket()->getFd())
                {
					try {
						Socket* clientSocket = server.connect(server.getSocket());
						KqueueManage::instance().setEvent(clientSocket->getFd(), EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
					} catch (IOException e) {}
                }
                else
                {
					bool b = KqueueManage::instance().recv(curr_event->ident);
					if (b == false) {
						server.clients().erase(curr_event->ident);
						KqueueManage::instance().delEvent(curr_event->ident);
					}
                }
            }
            else if (curr_event->filter == EVFILT_WRITE)
            {
				if (server.clients()[curr_event->ident]) {
					if (server.clients()[curr_event->ident]->response().isEnd() != true) {
						continue;
					}
					bool b = KqueueManage::instance().send(curr_event->ident);
					if (b == false) {
						server.clients().erase(curr_event->ident);
						delete server.clients()[curr_event->ident];
						KqueueManage::instance().delEvent(curr_event->ident);
					} else {
						server.clients().erase(curr_event->ident);
						delete server.clients()[curr_event->ident];
						KqueueManage::instance().delEvent(curr_event->ident);
					}
				} else {
					KqueueManage::instance().send(curr_event->ident);
				}
            } else {
			} 
		}
		for (std::list<Server*>::iterator it = _servers.begin(); it != _servers.end(); it++)
			(*it)->checkTimeout();
		if (this->_isStop == true) {
			if (KqueueManage::instance().eventCount() < 1) {
				this->_isRun = false;
				break;
			}
		}
    }


	while (!_servers.empty()) {
		ServerList::iterator it = _servers.begin();
		Server &server = *(*it);

		try {
			KqueueManage::instance().delEvent(server.getSocket()->getFd());
			server.close();
		}
		catch (Exception& exception) {
			std::cerr << "Failed to terminate: " + server.getHost() + ":" + Base::toString(server.getPort(),10) + ": " + exception.message() << std::endl;
		}
		delete &server;
		_servers.erase(it);
	}
}

Webserv* Webserv::create(void) {

	typedef std::map<int, std::list<ServerBlock*> > port_map;
	typedef port_map::const_iterator port_iterator;

	typedef std::map<std::string, port_map> host_map;
	typedef host_map::const_iterator host_iterator;

	host_map hostToPortToServersMap;

	RootBlock* rootBlock = Config::instance().rootBlock();
	
	std::list<ServerBlock*> serverBlocks = rootBlock->ServerBlockList();
	std::map<int, int> portMap;
	for (std::list<ServerBlock*>::iterator sit = serverBlocks.begin(); sit != serverBlocks.end(); sit++) {
		ServerBlock &serverBlock = *(*sit);
		
		std::string host = (serverBlock.getServerName().empty() == false) ? serverBlock.getServerName() : SHTTP::DEFAULT_HOST;
		int port = (serverBlock.getListen() != 0) ? serverBlock.getListen() : SHTTP::DEFAULT_PORT;
		hostToPortToServersMap[host][port].push_back(&serverBlock);

		if (port <= 0 || port >= std::numeric_limits<short>::max())
			throw RuntimeException("port " + Base::toString(port, 10) + " is out of range!");
		std::map<int, int>::iterator pit = portMap.find(port);
		if (pit == portMap.end())
			portMap[port] = port;
		else
			throw RuntimeException("port duplicated! (" + Base::toString(port, 10) + ")");
	}


	ServerList httpServers;
	for (host_iterator hit = hostToPortToServersMap.begin(); hit != hostToPortToServersMap.end(); hit++) {
		const std::string &host = hit->first;
		const port_map &portMap = hit->second;

		for (port_iterator pit = portMap.begin(); pit != portMap.end(); pit++) {
			int port = pit->first;
			std::list<ServerBlock*> serverBlocks = pit->second;

			httpServers.push_back(new Server(host, port, serverBlocks));
		}
	}
	return (new Webserv(httpServers));
}

void Webserv::stop(void) {
	for (ServerList::iterator it = _servers.begin(); it != _servers.end(); it++)
		KqueueManage::instance().delEvent((*it)->getSocket()->getFd());
	this->_isStop = true;
}
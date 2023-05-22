#include "Webserv.hpp"
#include "../config/block/ServerBlock.hpp"
#include "../config/Config.hpp"
#include "../iom/KqueueManage.hpp"
#include "../http/server/Server.hpp"
#include "../log/LogFactory.hpp"
#include "../util/Base.hpp"

Logger& Webserv::logger = LogFactory::get("Webserv");

Webserv::Webserv(void) {}
Webserv::Webserv(const ServerList& server) : _servers(server), _isRun(false), _isStop(false) {}

Webserv::Webserv(const Webserv& other) {}
Webserv& Webserv::operator=(const Webserv& other) { return (*this);}
Webserv::~Webserv(void) {}

void Webserv::run(void) {

	this->_servers.front()->init();
	this->_isRun = true;

    struct kevent* curr_event;
    while (this->_isRun) {
		KqueueManage::instance().kevent();
		std::cout << "KqueueManage::instance()._changeVec.size()" << KqueueManage::instance()._changeVec.size() << std::endl;
		(&KqueueManage::instance())->_changeVec.clear();
		std::cout << "kevent : " << KqueueManage::instance().eventCount() <<  std::endl;
        for (int i = 0; i < KqueueManage::instance().eventCount() ; ++i) {
            curr_event = &KqueueManage::instance().eventArr()[i];
			//  (&KqueueManage::instance())->changeVec().clear();
			std::cout << "curr_event->ident : " << curr_event->ident <<  " " << KqueueManage::instance().eventCount() <<  std::endl;
			
            if (curr_event->flags & EV_ERROR) {
                if (curr_event->ident == this->_servers.front()->getSocket()->getFd())
                    throw IOException("server socket error", errno);
                else
                {
					std::cerr << "error !!!!" << std::endl;
					// server.disconnect()
                }
            }
            else if (curr_event->filter == EVFILT_READ)
            {
                if (curr_event->ident == this->_servers.front()->getSocket()->getFd())
                {
                    /* accept new client */
					try {
						Socket* clientSocket = this->_servers.front()->connect(this->_servers.front()->getSocket());
						std::cout << "new:clientsocket : " <<  clientSocket->getFd() << " " << curr_event->ident << std::endl;
						KqueueManage::instance().setEvent(clientSocket->getFd(), EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
						// KqueueManage::instance().setEvent(clientSocket->getFd(), EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
					} catch (IOException e) {}
                }
                else
                {
					std::cout << "webserv:read : " << curr_event->ident  << std::endl;
                    /* read data from client */
					bool b = KqueueManage::instance().recv(curr_event->ident);
					if (b == false) {
						//std::cout <<"read false =================================================================";
						this->_servers.front()->clients().erase(curr_event->ident);
						KqueueManage::instance().delEvent(curr_event->ident);
						// throw IOException("recv error : ", errno);
					} else {
						// std::cout << "connect cnt : " << Client::_s_connCnt << std::endl;
                    }
                }
            }
            else if (curr_event->filter == EVFILT_WRITE)
            {
				std::cout << "writefilter: " << curr_event->ident <<  std::endl;
				if (this->_servers.front()->clients()[curr_event->ident]) {
					// std::cout << "server.clients()[curr_event->ident]->state() : " << server.clients()[curr_event->ident]->response().state() << std::endl;
					// if (server.clients()[curr_event->ident]->state() != server.clients()[curr_event->ident]->END) {
					if (this->_servers.front()->clients()[curr_event->ident]->response().isEnd() != true) {
					// if (!server.clients()[curr_event->ident]->in().storage().empty()) {
						// server.clients().erase(curr_event->ident);
						// KqueueManage::instance().delEvent(curr_event->ident);
						std::cout << "not end " << curr_event->ident << std::endl;
						continue;
					}
					bool b = KqueueManage::instance().send(curr_event->ident);
					if (b == false) {
						std::cout << "write fail " << std::endl;
						this->_servers.front()->clients().erase(curr_event->ident);
						delete this->_servers.front()->clients()[curr_event->ident];
						KqueueManage::instance().delEvent(curr_event->ident);
					} else {
						std::cout << "write treutrue" << std::endl;
						// this->_servers.front()->clients().erase(curr_event->ident);
						// delete this->_servers.front()->clients()[curr_event->ident];
						KqueueManage::instance().delEvent(curr_event->ident);
					}
				} else {
					KqueueManage::instance().send(curr_event->ident);
					//KqueueManage::instance().delEvent(curr_event->ident);
				}
            } else {
			} 
		}
		std::cout << "KqueueManage::instance()._changeVec.size() ebd?? " << KqueueManage::instance()._changeVec.size() << std::endl;
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
			// logger.error("Failed to terminate: " + server.getHost() + ":" + Base::toString(server.getPort(),10) + ": " + exception.message());
		}
		delete &server;
		_servers.erase(it);
	}
}

Webserv* Webserv::create(void) {
	ServerList list;
	list.push_back(new Server( Config::instance().rootBlock()->ServerBlockList().front()->getServerName()
							, Config::instance().rootBlock()->ServerBlockList().front()->getListen()
							, Config::instance().rootBlock()->ServerBlockList()));
	return (new Webserv(list));
}

void Webserv::stop(void) {
	for (ServerList::iterator it = _servers.begin(); it != _servers.end(); it++)
		KqueueManage::instance().delEvent((*it)->getSocket()->getFd());
	this->_isStop = true;
}
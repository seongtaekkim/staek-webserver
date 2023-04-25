#include "Webserv.hpp"
#include "../http/server/Server.hpp"
#include "../config/block/ServerBlock.hpp"
#include "../iom/KqueueManage.hpp"

Webserv::Webserv(void) {}
Webserv::Webserv(const Webserv& other) {}
Webserv& Webserv::operator=(const Webserv& other) { return (*this);}
Webserv::~Webserv(void) {}

/*
server & kqueue & client
*/
void Webserv::start(void) {
	std::list<ServerBlock *> sbs;
	Server server("127.0.0.1", 8080, sbs);
	server.init();

    /* main loop */
    struct kevent* curr_event;
    while (1)
    {
		usleep(1000); //  usleep(1000000); // delay setting
		KqueueManage::instance().kevent(); // KqueueManage::instance().changeVec().clear(); // 꼭 해야 하나 고민
		std::cout << "KqueueManage::instance()._changeVec.size()" << KqueueManage::instance()._changeVec.size() << std::endl;
		(&KqueueManage::instance())->_changeVec.clear();
		std::cout << "kevent" << std::endl;
        for (int i = 0; i < KqueueManage::instance().eventCount() ; ++i) {
            curr_event = &KqueueManage::instance().eventArr()[i];
			//  (&KqueueManage::instance())->changeVec().clear();
			std::cout << "!!!!!!!!!!!!!!!!=!!!!!!!!!!!!!!!! : " << curr_event->ident <<  " " << KqueueManage::instance().eventCount() <<  std::endl;
			
            if (curr_event->flags & EV_ERROR) {
                if (curr_event->ident == server.getSocket()->getFd())
                    throw IOException("server socket error", errno);
                else
                {
					std::cerr << "error !!!!" << std::endl;
					// server.disconnect()
                }
            }
            else if (curr_event->filter == EVFILT_READ)
            {
                if (curr_event->ident == server.getSocket()->getFd())
                {
                    /* accept new client */
					try {
						Socket* clientSocket = server.connect(server.getSocket());
						std::cout << "new:clientsocket : " <<  clientSocket->getFd() << " " << curr_event->ident << std::endl;
						KqueueManage::instance().setEvent(clientSocket->getFd(), EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
						KqueueManage::instance().setEvent(clientSocket->getFd(), EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);

					} catch (IOException e) {}
                }
                else
                {
					std::cout << "webserv:read : " << curr_event->ident  << std::endl;
                    /* read data from client */
					bool b = server.clients()[curr_event->ident]->recv(server.clients()[curr_event->ident]->socket());
					if (b == false) {
						std::cout <<"read false =================================================================";
						server.clients().erase(curr_event->ident);
						KqueueManage::instance().delEvent(curr_event->ident);
						// throw IOException("recv error : ", errno);
					} else {
						std::cout << "connect cnt : " << Client::_s_connCnt << std::endl;
                    }
                }
            }
            else if (curr_event->filter == EVFILT_WRITE)
            {
				std::cout << "writefilter: " << curr_event->ident <<  std::endl;
				if (server.clients()[curr_event->ident]->state() != server.clients()[curr_event->ident]->END) {
					server.clients().erase(curr_event->ident);
					KqueueManage::instance().delEvent(curr_event->ident);
					continue;
				}
				bool b = server.clients()[curr_event->ident]->send(server.clients()[curr_event->ident]->socket());
				if (b == false) {
					std::cout << "write fail " << std::endl;
					server.clients().erase(curr_event->ident);
					KqueueManage::instance().delEvent(curr_event->ident);
				} else {
					std::cout << "write treutrue" << std::endl;
					server.clients().erase(curr_event->ident);
				}
            } else {
				std::cout << "what is event ?? : " << curr_event->filter << std::endl;
			} 
		}
		std::cout << "KqueueManage::instance()._changeVec.size() ebd?? " << KqueueManage::instance()._changeVec.size() << std::endl;

    }
}

void Webserv::stop(void) {

}
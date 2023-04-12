NAME 		= webserv
CXX 		= c++
#CXXFLAGS 	= -Wall -Wextra -Werror -std=c++98
RM 			= rm -f
INCS 		= -I
SRCS 		= srcs/main.cpp srcs/log/LogFactory.cpp srcs/log/Logger.cpp \
				srcs/exception/Exception.cpp srcs/exception/RuntimeException.cpp srcs/exception/IOException.cpp srcs/exception/IllegalStateException.cpp srcs/exception/IllegalArgumentException.cpp srcs/exception/NullPointerException.cpp \
				srcs/file/FileDescriptor.cpp srcs/file/File.cpp \
				srcs/config/block/RootBlock.cpp srcs/config/block/ServerBlock.cpp srcs/config/block/LocationBlock.cpp srcs/config/Config.cpp srcs/config/Mime.cpp srcs/config/Reader.cpp \
				srcs/http/server/Server.cpp srcs/http/server/Socket.cpp \
				srcs/http/server/Client.cpp srcs/http/server/RWCallback.cpp srcs/http/Webserv.cpp srcs/http/SHTTP.cpp \
				srcs/http/response/HTTPState.cpp srcs/http/response/Response.cpp srcs/http/response/StatusLine.cpp \
				srcs/http/response/make/IMaker.cpp srcs/http/response/make/MethodMaker.cpp srcs/http/response/make/ResponseMaker.cpp \
				srcs/http/response/method/IMethod.cpp srcs/http/response/method/Method.cpp srcs/http/response/method/Get.cpp srcs/http/response/method/Post.cpp srcs/http/response/method/Delete.cpp \
				srcs/iom/KqueueManage.cpp \
				srcs/address/InetAddress.cpp \
				srcs/util/Storage.cpp srcs/http/server/SocketStorage.cpp \
				srcs/http/request/Request.cpp srcs/http/request/RequestHeaders.cpp srcs/http/request/RequestParser.cpp srcs/http/request/RequestString.cpp \
				srcs/http/parse/Parser.cpp
OBJS 		= $(SRCS:.cpp=.o)
.c.o :
	$(CXX) $(CXXFLAGS) -c $< -o $@
all : $(NAME)
$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re:
	make fclean
	make all
.PHONY: all clean fclean re
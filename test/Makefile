NAME 		= test
CXX 		= c++
# CXXFLAGS 	= -Wall -Wextra -Werror -std=c++98
CXXFLAGS 	= -g
RM 			= rm -f
SRCS 		=  ../srcs/log/LogFactory.cpp ../srcs/log/Logger.cpp \
			   test_main.cpp case/TestCase.cpp \
			   units/unit_libft_is.cpp \
			   units/unit_log.cpp \
			   units/unit_config.cpp \
			   ../srcs/util/Base64.cpp units/unit_base64.cpp \
			   ../srcs/main.cpp ../srcs/log/LogFactory.cpp ../srcs/log/Logger.cpp \
				../srcs/exception/Exception.cpp ../srcs/exception/RuntimeException.cpp ../srcs/exception/IOException.cpp ../srcs/exception/IllegalStateException.cpp ../srcs/exception/IllegalArgumentException.cpp ../srcs/exception/NullPointerException.cpp \
				../srcs/file/FileDescriptor.cpp ../srcs/file/File.cpp \
				../srcs/config/block/RootBlock.cpp ../srcs/config/block/ServerBlock.cpp ../srcs/config/block/LocationBlock.cpp ../srcs/config/Config.cpp ../srcs/config/Mime.cpp ../srcs/config/Reader.cpp \
				../srcs/http/server/Server.cpp ../srcs/http/server/Socket.cpp \
				../srcs/http/server/Client.cpp ../srcs/http/server/RWCallback.cpp ../srcs/http/Webserv.cpp ../srcs/http/SHTTP.cpp ../srcs/http/URL.cpp \
				../srcs/http/response/HTTPState.cpp ../srcs/http/response/Response.cpp ../srcs/http/response/StatusLine.cpp \
				../srcs/http/response/make/IMaker.cpp ../srcs/http/response/make/MethodMaker.cpp ../srcs/http/response/make/ResponseMaker.cpp \
				../srcs/http/response/method/IMethod.cpp ../srcs/http/response/method/Method.cpp ../srcs/http/response/method/Get.cpp ../srcs/http/response/method/Post.cpp ../srcs/http/response/method/Delete.cpp \
				../srcs/iom/KqueueManage.cpp \
				../srcs/address/InetAddress.cpp \
				../srcs/util/Storage.cpp ../srcs/http/server/SocketStorage.cpp \
				../srcs/http/request/Request.cpp ../srcs/http/request/RequestHeaders.cpp ../srcs/http/request/RequestParser.cpp ../srcs/http/request/RequestString.cpp \
				../srcs/http/parse/Parser.cpp ../srcs/http/parse/PathParser.cpp \
				../srcs/http/response/IBody.cpp ../srcs/http/response/ResponseByString.cpp ../srcs/http/response/ResponseByFile.cpp \
				../srcs/util/Time.cpp
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
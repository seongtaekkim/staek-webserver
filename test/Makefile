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
			   ../srcs/http/parse/Parser.cpp \
			   ../srcs/http/request/Request.cpp \
			   ../srcs/http/request/RequestString.cpp \
			   ../srcs/http/request/RequestParser.cpp \
			   ../srcs/http/request/RequestHeaders.cpp \
			   ../srcs/exception/IllegalStateException.cpp \
			   ../srcs/exception/RuntimeException.cpp \
			   ../srcs/exception/Exception.cpp ../srcs/exception/IOException.cpp \
			   ../srcs/config/Config.cpp ../srcs/config/Mime.cpp ../srcs/config/Reader.cpp ../srcs/config/block/RootBlock.cpp ../srcs/config/block/LocationBlock.cpp ../srcs/config/block/ServerBlock.cpp

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
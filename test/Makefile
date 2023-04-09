NAME 		= test
CXX 		= c++
# CXXFLAGS 	= -Wall -Wextra -Werror -std=c++98
CXXFLAGS 	= -g
RM 			= rm -f
SRCS 		=  ../srcs/log/LogFactory.cpp ../srcs/log/Logger.cpp \
			   test_main.cpp case/TestCase.cpp \
			   units/unit_libft_is.cpp \
			   units/unit_log.cpp \
			   units/unit_request.cpp \
			   ../srcs/http/parse/Parser.cpp \
			   ../srcs/http/request/Request.cpp \
			   ../srcs/http/request/RequestString.cpp \
			   ../srcs/http/request/RequestParser.cpp \
			   ../srcs/http/request/RequestHeaders.cpp \
			   ../srcs/exception/IllegalStateException.cpp \
			   ../srcs/exception/RuntimeException.cpp \
			   ../srcs/exception/Exception.cpp 

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
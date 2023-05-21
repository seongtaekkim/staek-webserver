#ifndef CGI_HPP
#define CGI_HPP

#include "../../config/Config.hpp"
#include "../../config/block/ServerBlock.hpp"
#include "../../file/FileDescriptor.hpp"
#include "../../file/File.hpp"
#include <sys/types.h>
#include "../../util/SEnvironment.hpp"
#include <string>

class CGITask;

class Logger;
class FileDescriptor;
class CGIBlock;
class Client;

class CGI {
	private:
		pid_t			_pid;
		FileDescriptor&	_in;
		FileDescriptor&	_out;
		File&			_file;
		bool			_killed;

	private:
		CGI(void);
		CGI(pid_t pid, FileDescriptor& in, FileDescriptor& out, File& file);
		CGI(const CGI& other);
		CGI& operator=(const CGI& other);

	public:
		virtual ~CGI();

		void kill(void);
		void wait(void);
		bool running(void);

		inline FileDescriptor& in() const {
			return (this->_in);
		}

		inline FileDescriptor& out() const {
			return (this->_out);
		}
		
		inline File& file() const {
			return (this->_file);
		}

		inline pid_t pid() const {
			return (_pid);
		}

	public:
		static CGITask* execute(Client& client, const ServerBlock::CgiType& cgiBlock, const SEnvironment& env);

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
		static const std::string REDIRECT_STATUS;
};

#endif

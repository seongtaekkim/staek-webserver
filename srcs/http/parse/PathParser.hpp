#ifndef PATHPARSER_HPP
#define PATHPARSER_HPP

#include <map>
#include <string>

class PathParser {
	public:
		enum State
		{
			S_PATH,
			S_QUERY_STRING_KEY,
			S_QUERY_STRING_VALUE,
			S_FRAGMENT,
			S_HEX_START,
			S_HEX_END,
			S_END,
		};

	public:
		// static DataSize MAX_LENGTH;

	private:
		State m_state;
		std::string _path;
		std::string m_original;
		std::string m_queryKey;
		std::string m_queryValue;
		State m_hexBeforeState;
		std::string m_hex;
		std::map<std::string, std::string> m_query;
		std::string m_fragment;
		long m_dot;
		long m_level;

	public:
		PathParser();

		void parse(char c);

		void
		reset();

		inline State
		state() const
		{
			return (m_state);
		}

		inline const std::string&
		path() const
		{
			return (_path);
		}

		inline const std::string&
		original() const
		{
			return (_path);
		}

		const std::map<std::string, std::string>& query() const
		{
			return (m_query);
		}

		const std::string&
		fragment() const
		{
			return (m_fragment);
		}

	private:
		void
		commitHexToPath(char c);

		void
		commitHexToKey(char c);

		void
		commitHexToValue(char c);

		void
		commitHexToFragment(char c);

		void
		commitQueryKeyValue(State nextState);

};

#endif

#ifndef IHTTPBODYENCODER_HPP
#define IHTTPBODYENCODER_HPP

#include <string>

class IHTTPBodyEncoder {
public:
	virtual ~IHTTPBodyEncoder(void);

	/**
	 * Encode a string.
	 *
	 * @param input Data to encode.
	 * @return Encoded data.
	 */
	virtual std::string encode(const std::string &input) = 0;

	/**
	 * Cleanup the memory after usage.
	 *
	 * For stateful and allocated, that mean delete-ing itself.
	 * For stateless, nothing is done.
	 */
	virtual void cleanup(void);
};

#endif

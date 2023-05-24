#include "HTTPBodyEncoding.hpp"

HTTPBodyEncoding::~HTTPBodyEncoding(void) {}

IHTTPBodyDecoder* HTTPBodyEncoding::decodeSelector(const Header& headerFields) {
	std::string transfertEncodingOpt = headerFields.get(Header::TRANSFER_ENCODING);
	if (!transfertEncodingOpt.empty()) {
		if (transfertEncodingOpt == Header::CHUNKED)
			return (new ChunkDecoder(true));

		throw Exception("unsupported transfert-encoding:" + transfertEncodingOpt);
	}

	std::string contentLengthOpt = headerFields.get(Header::CONTENT_LENGTH);
	if (!contentLengthOpt.empty()) {
		try {
			long long length = Base::convert<long long>(contentLengthOpt, Base::DECIMAL);

			if (length == 0)
				return (NULL);
			return (new IdentityDecoder(true, length));
		}
		catch (Exception& exception) {
			throw Exception("content-length `" + contentLengthOpt + "` is not a valid number: " + exception.message());
		}
	}

	throw Exception("no transfert-encoding or content-length");
}

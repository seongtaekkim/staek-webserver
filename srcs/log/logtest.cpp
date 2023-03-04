
#include "LogFactory.hpp"


Logger log = LogFactory::get("Configuration");

int main(void) {
	log.error("awefawef" );
	log.error("awefawef" );
	log.error("awefawef" );
	log.error("awefawef" );
	// LOG.trace() << "Root Block: " << rootBlock << std::endl;
}
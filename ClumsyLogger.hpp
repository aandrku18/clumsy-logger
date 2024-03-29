#include <string>
#ifndef CLUMSY_LOGGER
#define CLUMSY_LOGGER

class ClumsyLogger {
	public:
		//constructor
		ClumsyLogger();

		//destructor
		~ClumsyLogger();


		//log with FATAL severity
		void fatal(std::string message);

		//log with ERROR severity 
		void error(std::string message);
		
		//log with WARN severity
		void warn(std::string message);

		//log with INFO severity
		void info(std::string message);

		//log with DEBUG severity
		void debug(std::string message);

		//log with TRACE severity
		void trace(std::string message);
	private:
};


#endif

#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

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
		//logs queue
		std::queue<std::string> logQueue;

		//mutex
		std::mutex m;

		//worker thread
		std::thread worker;

		//condition condition_variable
		std::condition_variable cv;

		//flag to stop worker thread
		bool stop;

		//start processing logging queue
		void processQueue();
		
		//get current time
		std::string getCurrentTimestamp();
};


#endif

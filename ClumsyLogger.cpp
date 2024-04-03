#include "ClumsyLogger.hpp"
#include <mutex>
#include <unistd.h>

ClumsyLogger::ClumsyLogger() {
	stop = false;
	worker = std::thread(&ClumsyLogger::processQueue, this);
}

ClumsyLogger::~ClumsyLogger() {
	{
		std::unique_lock<std::mutex> lock(m);	
		stop = true;
	}
	cv.notify_one();
	worker.join();
}

void ClumsyLogger::fatal(std::string message) {
	std::lock_guard<std::mutex> lock(m);
	logQueue.push("FATAL: " + getCurrentTimestamp() + " --- " + message);
	cv.notify_one();
}

void ClumsyLogger::error(std::string message) {
	std::lock_guard<std::mutex> lock(m);
	logQueue.push("ERROR: " + getCurrentTimestamp() + " --- " + message);
	cv.notify_one();
}

void ClumsyLogger::info(std::string message) {
	std::lock_guard<std::mutex> lock(m);
	logQueue.push("INFO: " + getCurrentTimestamp() + " --- " + message);
	cv.notify_one();
}

void ClumsyLogger::debug(std::string message) {
	std::lock_guard<std::mutex> lock(m);
	logQueue.push("DEBUG: " + getCurrentTimestamp() + " --- " + message);
	cv.notify_one();
}

void ClumsyLogger::trace(std::string message) {
	std::lock_guard<std::mutex> lock(m);
	logQueue.push("TRACE: " + getCurrentTimestamp() + " --- " + message);
	cv.notify_one();
}

void ClumsyLogger::processQueue() {
	while (!stop) {
		std::unique_lock<std::mutex> lk(m);
		cv.wait(lk, [this] { return !logQueue.empty() || !stop; });
		while (!logQueue.empty()) {
			std::string message = logQueue.front();
			logQueue.pop();
			std::cout << message << std::endl;
		}
	}
}

std::string ClumsyLogger::getCurrentTimestamp() {
  // Get the current time point
  auto now = std::chrono::system_clock::now();

  // Convert the time point to a time_t object
  std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

  // Convert the time_t object to a struct tm object
  std::tm *localTime = std::localtime(&currentTime);

  // Format the timestamp
  std::ostringstream oss;
  oss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");

  return oss.str();
}

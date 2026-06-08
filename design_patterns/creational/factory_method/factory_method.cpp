#include "factory_method.h"

#include <iostream>
#include <memory>
#include <string>

void FileLogger::log(std::string& message) {
    // Simulate logging to a file
    std::cout << "[FileLogger] " << message << std::endl;
}
std::unique_ptr<Logger> FileLoggerFactory::create() {
    return std::make_unique<FileLogger>();
}

void ConsoleLogger::log(std::string& message) {
    // Simulate logging to console
    std::cout << "[ConsoleLogger] " << message << std::endl;
}
std::unique_ptr<Logger> ConsoleLoggerFactory::create() {
    return std::make_unique<ConsoleLogger>();
}


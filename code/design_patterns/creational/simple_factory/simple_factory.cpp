#include "simple_factory.h"

#include <iostream>
#include <string>

void FileLogger::log(std::string& message) {
    // Simulate logging to a file
    std::cout << "[FileLogger] " << message << std::endl;
}

void ConsoleLogger::log(std::string& message) {
    // Simulate logging to console
    std::cout << "[ConsoleLogger] " << message << std::endl;
}

void NetworkLogger::log(std::string& message) {
    // Simulate logging over the network
    std::cout << "[NetworkLogger] " << message << std::endl;
}

std::unique_ptr<Logger> LoggerFactory::createLogger(LoggerType type) {
    switch (type) {
        case FILE_LOGGER:
            return std::make_unique<FileLogger>();
        case CONSOLE_LOGGER:
            return std::make_unique<ConsoleLogger>();
        case NETWORK_LOGGER:
            return std::make_unique<NetworkLogger>();
        default:
            return nullptr;
    }
}


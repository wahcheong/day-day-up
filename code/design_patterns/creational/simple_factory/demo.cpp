#include "simple_factory.h"

int main() {
    std::string message = "This is a log message.";

    auto fileLogger = LoggerFactory::createLogger(LoggerFactory::FILE_LOGGER);
    fileLogger->log(message);

    auto consoleLogger = LoggerFactory::createLogger(LoggerFactory::CONSOLE_LOGGER);
    consoleLogger->log(message);

    auto networkLogger = LoggerFactory::createLogger(LoggerFactory::NETWORK_LOGGER);
    networkLogger->log(message);

    return 0;
}

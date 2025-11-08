#include "factory_method.h"

int main() {
    std::string message = "This is a log message.";

    std::unique_ptr<LoggerFactory> fileFactory = std::make_unique<FileLoggerFactory>();
    auto fileLogger = fileFactory->create();
    fileLogger->log(message);

    std::unique_ptr<LoggerFactory> consoleFactory = std::make_unique<ConsoleLoggerFactory>();
    auto consoleLogger = consoleFactory->create();
    consoleLogger->log(message);

    return 0;
}

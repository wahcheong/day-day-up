#pragma once

#include <memory>
#include <string>

class Logger {
 public:
  virtual void log(std::string& message) = 0;
  // 作为基类，必须要有虚析构函数
  virtual ~Logger() = default;
};

class FileLogger : public Logger {
 public:
  void log(std::string& message) override;
};


class ConsoleLogger : public Logger {
 public:
  void log(std::string& message) override;
};

class NetworkLogger : public Logger {
 public:
  void log(std::string& message) override;
};

class LoggerFactory {
 public:
  enum LoggerType {
    FILE_LOGGER,
    CONSOLE_LOGGER,
    NETWORK_LOGGER
  };

  static std::unique_ptr<Logger> createLogger(LoggerType type);
};


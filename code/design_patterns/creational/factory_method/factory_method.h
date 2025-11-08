#pragma once

#include <memory>
#include <string>

// Logger Interface
class Logger {
 public:
  virtual void log(std::string& message) = 0;
  // 作为基类，必须要有虚析构函数
  virtual ~Logger() = default;
};

// Logger Factory Interface
class LoggerFactory {
 public:
  virtual std::unique_ptr<Logger> create() = 0;
  virtual ~LoggerFactory() = default;
};

// Concrete Logger: FileLogger
class FileLogger : public Logger {
 public:
  void log(std::string& message) override;
};

// Factory for FileLogger
class FileLoggerFactory : public LoggerFactory {
 public:
  std::unique_ptr<Logger> create() override;
};

// Concrete Logger: ConsoleLogger
class ConsoleLogger : public Logger {
 public:
  void log(std::string& message) override;
};

// Factory for ConsoleLogger
class ConsoleLoggerFactory : public LoggerFactory {
 public:
  std::unique_ptr<Logger> create() override;
};

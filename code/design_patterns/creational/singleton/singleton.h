#pragma once

#include <map>
#include <string>

class ConfigManager {
 public:
  // 删除拷贝构造和赋值操作
  ConfigManager(const ConfigManager&) = delete;
  ConfigManager& operator=(const ConfigManager&) = delete;

  static ConfigManager& getInstance() {
    // 局部静态变量，确保线程安全的单例实例
    static ConfigManager instance;
    return instance;
  }

  // 示例方法：设置配置项
  void setConfig(const std::string& key, const std::string& value);
  // 示例方法：获取配置项
  std::string getConfig(const std::string& key) const;

 private:
  // 私有构造函数，防止外部实例化
  ConfigManager() = default;

 private:
  // 示例成员变量，假设这个单例类被用于管理应用程序的配置
  std::map<std::string, std::string> config_;
};

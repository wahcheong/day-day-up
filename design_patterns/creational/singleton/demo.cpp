#include "singleton.h"

#include <iostream>

int main() {
  ConfigManager& config = ConfigManager::getInstance();
  config.setConfig("app_name", "day-day-up");

  ConfigManager& config_again = ConfigManager::getInstance();
  std::cout << "app_name: " << config_again.getConfig("app_name") << std::endl;

  return 0;
}

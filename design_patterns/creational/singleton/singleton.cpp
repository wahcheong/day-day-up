#include "singleton.h"

void ConfigManager::setConfig(const std::string& key, const std::string& value) {
    config_[key] = value;
}

std::string ConfigManager::getConfig(const std::string& key) const {
    auto it = config_.find(key);
    if (it != config_.end()) {
        return it->second;
    }
    return "";
}

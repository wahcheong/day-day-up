#include "adapter.h"

// 用户端代码，使用地图接口，不直接依赖具体的地图实现
void ClientCallingMap(std::unique_ptr<Map> map) {
  std::pair<double, double> from = {116.407396, 39.904200}; // 北京
  std::pair<double, double> to = {121.473701, 31.230416};   // 上海

  std::string travelInfo = map->getTravelInfo(from, to);
  std::cout << "Travel Info: " << travelInfo << std::endl;
}

int main() {
  // 使用适配器模式
  std::unique_ptr<Map> amapAdapter = std::make_unique<AmapAdapter>();
  ClientCallingMap(std::move(amapAdapter));

  return 0;
}

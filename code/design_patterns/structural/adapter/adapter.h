#pragma once

#include <iostream>
#include <string>

// 地图类，作为适配器模式的目标接口
// 假设这是辅助驾驶系统中使用的地图类，这是被适配的接口
class Map {
  public:
    // 计算从起点到终点的距离和时间等信息，返回xml格式的字符串
    virtual std::string getTravelInfo(
        const std::pair<double, double> &from,
        const std::pair<double, double> &to) {
      // 模拟地图的路线计算逻辑
      return "<route><distance>1000</distance><duration>500</duration></route>";
    }
    virtual ~Map() = default;
};

// 高德地图类，作为适配器模式的适配者
class Amap {
  public:
    // 高德地图的接口，返回json格式的字符串
    std::string calculateRoute(
        const std::pair<double, double> &from,
        const std::pair<double, double> &to) {
      // 模拟高德地图的路线计算逻辑
      return "{\"distance\": 1200, \"duration\": 600}";
    }
};

// 高德地图适配器类，实现目标接口Map
class AmapAdapter : public Map {
  public:
    AmapAdapter() : amap_(std::make_unique<Amap>()) {}

    std::string getTravelInfo(
        const std::pair<double, double> &from,
        const std::pair<double, double> &to) override {
      // 使用高德地图的接口计算路线
      std::string jsonResult = amap_->calculateRoute(from, to);
      // 将json格式转换为xml格式（这里简化处理，实际转换可能更复杂）
      std::string xmlResult = "<route><distance>1200</distance><duration>600</duration></route>";
      return xmlResult;
    }

  private:
    std::unique_ptr<Amap> amap_;
};

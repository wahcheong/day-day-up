#include "abstract_factory.h"

#include <string>

int main() {
  // 客户端代码
  std::unique_ptr<GUIFactory> factory;

  // 根据配置选择具体的工厂
  std::string os = "MacOS";  // 假设这是从配置文件或环境变量中读取的
  if (os == "Windows") {
    factory = std::make_unique<WindowsFactory>();
  } else if (os == "MacOS") {
    factory = std::make_unique<MacOSFactory>();
  }

  // 使用工厂创建产品，后续代码与具体工厂无关，实现了解耦
  auto button = factory->createButton();
  auto checkbox = factory->createCheckbox();

  // 渲染UI组件
  button->render();
  checkbox->render();

  return 0;
}

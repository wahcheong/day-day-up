#include "builder.h"

std::string BubbleTea::baseToString(Base base) const {
  switch (base) {
    case BLACK_TEA:
      return "红茶";
    case GREEN_TEA:
      return "绿茶";
    case OOLONG_TEA:
      return "乌龙茶";
    case NO_BASE:
      return "去茶底";
    default:
      return "未知茶底";
  }
}

std::string BubbleTea::sweetnessToString(SweetnessLevel level) const {
  switch (level) {
    case NO_SUGAR:
      return "无糖";
    case LESS_SUGAR:
      return "少糖";
    case FULL_SUGAR:
      return "全糖";
    default:
      return "未知甜度";
  }
}

std::string BubbleTea::iceToString(IceLevel level) const {
  switch (level) {
    case NO_ICE:
      return "去冰";
    case LESS_ICE:
      return "少冰";
    case NORMAL_ICE:
      return "正常冰";
    default:
      return "未知冰块量";
  }
}

std::string BubbleTea::toppingToString(Topping topping) const {
  switch (topping) {
    case PEARLS:
      return "珍珠";
    case COCONUT_JELLY:
      return "椰果";
    case PUDDING:
      return "布丁";
    default:
      return "未知配料";
  }
}

void BubbleTea::display() const {
  // 显示奶茶信息的逻辑
  std::cout << "Bubble Tea created with price: $" << price_ << std::endl;
  std::cout << "Details:" << std::endl;
  std::cout << "Base: " << baseToString(base_) << std::endl;
  std::cout << "Sweetness: " << sweetnessToString(sweetness_) << std::endl;
  std::cout << "Ice Level: " << iceToString(ice_) << std::endl;
  std::cout << "Toppings: ";
  for (const auto& topping : toppings_) {
    std::cout << toppingToString(topping) << " ";
  }
  std::cout << std::endl;
}

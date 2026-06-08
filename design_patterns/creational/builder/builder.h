#pragma once

#include <iostream>
#include <string>
#include <vector>

class BubbleTea {
 public:
  // 前向声明
  class Builder;

  enum Base { BLACK_TEA, GREEN_TEA, OOLONG_TEA, NO_BASE };
  std::string baseToString(Base base) const;

  enum SweetnessLevel { NO_SUGAR = 0, LESS_SUGAR = 1, FULL_SUGAR = 2 };
  std::string sweetnessToString(SweetnessLevel level) const;

  enum IceLevel { NO_ICE = 0, LESS_ICE = 1, NORMAL_ICE = 2 };
  std::string iceToString(IceLevel level) const;

  enum Topping { PEARLS, COCONUT_JELLY, PUDDING };
  std::string toppingToString(Topping topping) const;

  void display() const;

 private:
  // 友元类声明
  friend class Builder;
  // 私有构造函数，只能通过Builder创建实例
  BubbleTea(Base base, SweetnessLevel sweetness, IceLevel ice,
            const std::vector<Topping>& toppings, double price)
      : base_(base), sweetness_(sweetness), ice_(ice), toppings_(toppings), price_(price) {}

 private:
  // 茶底，例如：红茶、绿茶、去茶底
  Base base_;
  // 甜度，例如：无糖、少糖、全糖
  SweetnessLevel sweetness_;
  // 冰块量，例如：去冰、少冰、正常冰
  IceLevel ice_;
  // 配料，例如：珍珠、椰果、布丁
  std::vector<Topping> toppings_;
  // 价格
  double price_;
};

class BubbleTea::Builder {
 public:
  Builder& setBase(Base base) {
    base_ = base;
    return *this;
  }

  Builder& setSweetness(SweetnessLevel sweetness) {
    sweetness_ = sweetness;
    return *this;
  }

  Builder& setIce(IceLevel ice) {
    ice_ = ice;
    return *this;
  }

  Builder& addTopping(Topping topping) {
    toppings_.push_back(topping);
    return *this;
  }

  BubbleTea build() {
    return BubbleTea(base_, sweetness_, ice_, toppings_, price_);
  }
 private:
  // 茶底，例如：红茶、绿茶、去茶底
  Base base_ = GREEN_TEA;
  // 甜度，例如：无糖、少糖、全糖
  SweetnessLevel sweetness_ = FULL_SUGAR;
  // 冰块量，例如：去冰、少冰、正常冰
  IceLevel ice_ = NORMAL_ICE;
  // 配料，例如：珍珠、椰果、布丁
  std::vector<Topping> toppings_;
  // 价格
  double price_ = 5.0;
};

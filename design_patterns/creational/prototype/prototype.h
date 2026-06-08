#pragma once

#include <iostream>
#include <string>
#include <vector>

// 以游戏角色创建为例，展示原型模式
class GameCharacter {
 public:
  enum CharacterType { HUMAN, ELF, ORC };
  virtual std::unique_ptr<GameCharacter> Clone() const = 0;
  virtual void display() const = 0;
  virtual ~GameCharacter() = default;
};

class Human : public GameCharacter {
 public:
  Human(const std::string& name, int level) : name_(name), level_(level) {}
  std::unique_ptr<GameCharacter> Clone() const override {
    return std::make_unique<Human>(*this);
  }
  void display() const override {
    std::cout << "Human Character - Name: " << name_ << ", Level: " << level_ << std::endl;
  }
 private:
  std::string name_;
  int level_;
  // 其他属性如力量、敏捷等，真实的游戏角色会有更多属性，角色的构造也更复杂
};

class Elf : public GameCharacter {
 public:
  Elf(const std::string& name, int level) : name_(name), level_(level) {}
  std::unique_ptr<GameCharacter> Clone() const override {
    return std::make_unique<Elf>(*this);
  }
  void display() const override {
    std::cout << "Elf Character - Name: " << name_ << ", Level: " << level_ << std::endl;
  }
 private:
  std::string name_;
  int level_;
  // 其他属性如力量、敏捷等，真实的游戏角色会有更多属性，角色的构造也更复杂
};

class Orc : public GameCharacter {
 public:
  Orc(const std::string& name, int level) : name_(name), level_(level) {}
  std::unique_ptr<GameCharacter> Clone() const override {
    return std::make_unique<Orc>(*this);
  }
  void display() const override {
    std::cout << "Orc Character - Name: " << name_ << ", Level: " << level_ << std::endl;
  }
 private:
  std::string name_;
  int level_;
  // 其他属性如力量、敏捷等，真实的游戏角色会有更多属性，角色的构造也更复杂
};

class CharacterRegistry {
 public:
  CharacterRegistry() {
    registerPrototype(GameCharacter::HUMAN, std::make_unique<Human>("Default Human", 1));
    registerPrototype(GameCharacter::ELF, std::make_unique<Elf>("Default Elf", 2));
    registerPrototype(GameCharacter::ORC, std::make_unique<Orc>("Default Orc", 3));
  }

  void registerPrototype(GameCharacter::CharacterType type, std::unique_ptr<GameCharacter> prototype) {
    prototypes_[type] = std::move(prototype);
  }

  std::unique_ptr<GameCharacter> createCharacter(GameCharacter::CharacterType type) {
    auto it = prototypes_.find(type);
    if (it != prototypes_.end()) {
      return it->second->Clone();
    }
    return nullptr;
  }

 private:
  std::unordered_map<GameCharacter::CharacterType, std::unique_ptr<GameCharacter>> prototypes_;
};

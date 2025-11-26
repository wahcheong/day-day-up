#include "prototype.h"
#include <iostream>

int main() {
  // 方法一：直接创建一个角色实例作为原型
  // 创建一个原型角色
  std::unique_ptr<GameCharacter> elf_character = std::make_unique<Elf>("Legolas", 10);
  elf_character->display();

  // 克隆角色，这是原型模式的核心
  std::unique_ptr<GameCharacter> elf_character_copy = elf_character->Clone();
  elf_character_copy->display();

  // 方法二：使用注册表管理多个原型
  // 注册表构造的时候已经注册了三种角色类型
  CharacterRegistry registry;
  // 直接通过注册表创建角色
  std::unique_ptr<GameCharacter> human_character = registry.createCharacter(GameCharacter::HUMAN);
  human_character->display();

  return 0;
}

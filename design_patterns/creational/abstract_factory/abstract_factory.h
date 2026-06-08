#pragma once

#include <iostream>
#include <memory>

// 抽象产品接口
class Button {
 public:
  virtual void render() = 0;
  virtual ~Button() = default;
};
class Checkbox {
 public:
  virtual void render() = 0;
  virtual ~Checkbox() = default;
};
class GUIFactory {
 public:
  virtual std::unique_ptr<Button> createButton() = 0;
  virtual std::unique_ptr<Checkbox> createCheckbox() = 0;
  virtual ~GUIFactory() = default;
};


// Windows产品家族
class WindowsButton : public Button {
 public:
  void render() override {
    // Windows-specific button rendering logic
    std::cout << "Rendering Windows Button" << std::endl;
  }
};
class WindowsCheckbox : public Checkbox {
 public:
  void render() override {
    // Windows-specific checkbox rendering logic
    std::cout << "Rendering Windows Checkbox" << std::endl;
  }
};
class WindowsFactory : public GUIFactory {
 public:
  std::unique_ptr<Button> createButton() override {
    return std::make_unique<WindowsButton>();
  }
  std::unique_ptr<Checkbox> createCheckbox() override {
    return std::make_unique<WindowsCheckbox>();
  }
};

// MacOS产品家族
class MacOSButton : public Button {
 public:
  void render() override {
    // MacOS-specific button rendering logic
    std::cout << "Rendering MacOS Button" << std::endl;
  }
};
class MacOSCheckbox : public Checkbox {
 public:
  void render() override {
    // MacOS-specific checkbox rendering logic
    std::cout << "Rendering MacOS Checkbox" << std::endl;
  }
};
class MacOSFactory : public GUIFactory {
 public:
  std::unique_ptr<Button> createButton() override {
    return std::make_unique<MacOSButton>();
  }
  std::unique_ptr<Checkbox> createCheckbox() override {
    return std::make_unique<MacOSCheckbox>();
  }
};


#pragma once

#include <iostream>
#include <string>

// 桥接模式示例：使用不同的渲染API渲染图形

// 抽象类，表示渲染API
class RenderAPI {
 public:
  virtual void renderCircle(float x, float y, float radius) = 0;
  virtual ~RenderAPI() = default;
};

// OpenGL渲染API
class OpenGLRenderAPI : public RenderAPI {
 public:
  void renderCircle(float x, float y, float radius) override {
    std::cout << "Rendering Circle using OpenGL at (" << x << ", " << y
              << ") with radius " << radius << std::endl;
  }
};

// DirectX渲染API
class DirectXRenderAPI : public RenderAPI {
 public:
  void renderCircle(float x, float y, float radius) override {
    std::cout << "Rendering Circle using DirectX at (" << x << ", " << y
              << ") with radius " << radius << std::endl;
  }
};

// 表示图形，持有一个RenderAPI
class Shape {
 public:
  Shape(std::shared_ptr<RenderAPI> renderAPI) : render_api_(renderAPI) {}
  virtual void draw() = 0;
  virtual ~Shape() = default;

 protected:
  std::shared_ptr<RenderAPI> render_api_;
};

// 实现类：圆形
// Circle类通过桥接模式将Shape和RenderAPI解耦
class Circle : public Shape {
 public:
  Circle(float x, float y, float radius, std::shared_ptr<RenderAPI> render_api)
      : Shape(render_api), x_(x), y_(y), radius_(radius) {}
  void draw() override {
    render_api_->renderCircle(x_, y_, radius_);
  }

 private:
  float x_;
  float y_;
  float radius_;
};

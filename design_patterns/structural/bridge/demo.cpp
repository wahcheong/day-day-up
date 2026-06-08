#include "bridge.h"

int main() {
  // 创建OpenGL渲染API
  std::shared_ptr<RenderAPI> opengl_api = std::make_shared<OpenGLRenderAPI>();
  // 创建DirectX渲染API
  std::shared_ptr<RenderAPI> directx_api = std::make_shared<DirectXRenderAPI>();

  // 使用OpenGL渲染一个圆形
  Circle circle1(10, 20, 5, opengl_api);
  circle1.draw();

  // 使用DirectX渲染一个圆形
  Circle circle2(30, 40, 10, directx_api);
  circle2.draw();

  return 0;
}

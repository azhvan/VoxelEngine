#include "Window/Window.h"

constexpr int WIDTH = 1280;
constexpr int HEIGHT = 720;

int main() {
  Window::initialize(WIDTH, HEIGHT, "Window");
  Window::run();
  Window::terminate();
  return 0;
}


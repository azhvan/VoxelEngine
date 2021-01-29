#pragma once
#ifndef WINDOW_WINDOW_H
#define WINDOW_WINDOW_H
class GLFWwindow;

class Window {
public:
  static GLFWwindow* window;
  static int initialize(int width, int height, const char* title);
  static void terminate();

  static bool isShouldClose();
  static void setShouldClose(bool flag);
  static void swapBuffers();
};
#endif // !WINDOW_WINDOW_H



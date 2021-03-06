#pragma once
#ifndef WINDOW_WINDOW_H
#define WINDOW_WINDOW_H
#include <string>
class GLFWwindow;

class Window {
public:
  static int width;
	static int height;
  static GLFWwindow* window;
  static int initialize(int width, int height, const std::string& title);
  static void terminate();

  static void run();

  static void setCursorMode(int mode);
  static bool isShouldClose();
  static void setShouldClose(bool flag);
  static void swapBuffers();
};
#endif // !WINDOW_WINDOW_H



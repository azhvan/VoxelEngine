#pragma once
#ifndef WINDOW_EVENTS_H
#define WINDOW_EVENTS_H

#include "Window.h"
typedef unsigned int uint;

class Events {
public:
  static bool* _keys;
  static uint* _frames;
  static uint _current;
  static double deltaX;
  static double deltaY;
  static double x;
  static double y;
  static bool _cursor_locked;
  static bool _cursor_started;

  static int initialize();
  static void pullEvents();

  static bool pressed(int keycode);
  static bool jpressed(int keycode);

  static bool clicked(int button);
  static bool jclicked(int button);
};
#endif // !WINDOW_EVENTS_H
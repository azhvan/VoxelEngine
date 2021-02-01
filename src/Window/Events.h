#pragma once
#ifndef WINDOW_EVENTS_H
#define WINDOW_EVENTS_H
typedef unsigned int uint;

class Events {
public:
  static bool* keys;
  static uint* frames;
  static uint current;
  static double deltaX;
  static double deltaY;
  static double x;
  static double y;
  static bool cursor_locked;
  static bool cursor_started;

  static int initialize();
  static void pollEvents();

  static bool pressed(int keycode);
  static bool jpressed(int keycode);

  static bool clicked(int button);
  static bool jclicked(int button);

  static void toogleCursor();
};
#endif // !WINDOW_EVENTS_H

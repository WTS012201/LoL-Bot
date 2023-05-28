#include "input.hpp"

const void input::mouseClick(const int button, const int wait) {
  Display *display = XOpenDisplay(NULL);
  XEvent event;

  if (display == NULL) {
    fprintf(stderr, "Cannot initialize the display\n");
    exit(EXIT_FAILURE);
  }
  memset(&event, 0x00, sizeof(event));
  event.type = ButtonPress;
  event.xbutton.button = button;
  event.xbutton.same_screen = True;
  XQueryPointer(display, RootWindow(display, DefaultScreen(display)),
                &event.xbutton.root, &event.xbutton.window,
                &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x,
                &event.xbutton.y, &event.xbutton.state);
  event.xbutton.subwindow = event.xbutton.window;
  while (event.xbutton.subwindow) {
    event.xbutton.window = event.xbutton.subwindow;
    XQueryPointer(display, event.xbutton.window, &event.xbutton.root,
                  &event.xbutton.subwindow, &event.xbutton.x_root,
                  &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y,
                  &event.xbutton.state);
  }
  if (XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0)
    fprintf(stderr, "Mouse Error\n");

  XFlush(display);
  std::this_thread::sleep_for(std::chrono::milliseconds(wait));

  event.type = ButtonRelease;
  event.xbutton.state = 0x100;

  if (XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0)
    fprintf(stderr, "Mouse Error\n");
  XFlush(display);
  XCloseDisplay(display);
}

const void input::keyPress(const int XKeyCode, const int wait) {
  Display *display;
  unsigned int keycode;

  display = XOpenDisplay(NULL);
  keycode = XKeysymToKeycode(display, XKeyCode);
  XTestFakeKeyEvent(display, keycode, True, 0);
  std::this_thread::sleep_for(std::chrono::milliseconds(wait));
  XTestFakeKeyEvent(display, keycode, False, 0);
  XFlush(display);
}
const void input::move(const int x, const int y) {
  Display *display = XOpenDisplay(0);
  Window root = DefaultRootWindow(display);
  XWarpPointer(display, None, root, 0, 0, 0, 0, x, y);
  XFlush(display);
}
const void input::moveAndClick(const int x, const int y, const int XKeyCode) {
  move(x, y);
  mouseClick(XKeyCode);
}

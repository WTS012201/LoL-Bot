#ifndef __INPUT_H
#define __INPUT_H

#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <unistd.h>

#include <X11/Intrinsic.h>
#include <X11/Xlib.h>
#include <X11/Xresource.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>

#define L_BUTTON Button1
#define M_BUTTON Button2
#define R_BUTTON Button3

namespace input {
const void mouseClick(const int button, const int wait = 0);
const void keyPress(const int XKeyCode, const int wait = 0);
const void move(const int x, const int y);
const void moveAndClick(const int x, const int y, const int XKeyCode);
}; // namespace input
#endif

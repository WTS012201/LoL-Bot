#ifndef __SCREEN_CAPTURE_H
#define __SCREEN_CAPTURE_H

#ifndef __OPENCV_H
#define __OPENCV_H
#include <opencv2/opencv.hpp>
#endif

#include <X11/Xlib.h>
#include <X11/Xutil.h>

class ScreenCapture {
private:
  Display *display;
  Window root;
  int x, y, width, height;
  XImage *img{nullptr};

public:
  ScreenCapture();
  ScreenCapture(int x, int y, int width, int height);
  void operator()(cv::Mat &cvImg);
  ~ScreenCapture();
};

#endif

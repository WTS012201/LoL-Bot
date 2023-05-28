#include "screen.hpp"

ScreenCapture::ScreenCapture() : x(0), y(0), width(1920), height(1080) {}

ScreenCapture::ScreenCapture(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height) {
  display = XOpenDisplay(nullptr);
  root = DefaultRootWindow(display);
}

void ScreenCapture::operator()(cv::Mat &cvImg) {
  if (img != nullptr)
    XDestroyImage(img);
  img = XGetImage(display, root, x, y, width, height, AllPlanes, ZPixmap);
  cvImg = cv::Mat(height, width, CV_8UC4, img->data);
}

ScreenCapture::~ScreenCapture() {
  if (img != nullptr)
    XDestroyImage(img);
  XCloseDisplay(display);
}

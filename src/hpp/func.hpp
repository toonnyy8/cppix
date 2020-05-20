#ifndef __CPPIX_FUNC__
#define __CPPIX_FUNC__
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include "./struct.hpp"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
namespace cppix {
std::string decode_color(char color_code) {
  std::string color_str;
  color_str = "";
  int cc;
  cc = (int)color_code;

  color_str = (char)(cc % 10 + 48);
  cc /= 10;
  color_str = (char)(cc % 10 + 48) + color_str;
  cc /= 10;
  color_str = (char)(cc % 10 + 48) + color_str;

  return color_str;
}
std::string color(struct cppix::RGBA rgba, std::string pixel_str = "  ") {
  if (!rgba.a)
    return "\x1b[48;2;" + decode_color(rgba.r) + ";" + decode_color(rgba.g) +
           ";" + decode_color(rgba.b) + "m" + pixel_str + "\x1b[0m";
  else
    return pixel_str;
}

template <typename T> T key_In(void) {
  T value;
  std::cin >> value;
  return value;
}

template <typename T> T key_In(std::string message) {
  std::cout << message;
  T value;
  std::cin >> value;
  return value;
}

template <typename T> T key_In(std::string message, T value) {
  std::cout << message << value << std::endl;
  return value;
}

void draw_map(struct cppix::Viewport vp, struct cppix::PixelMap pm, int frame) {
  for (int y = vp.offset_y; y < MIN(vp.offset_y + vp.height, pm.height); y++) {
    for (int x = vp.offset_x; x < MIN(vp.offset_x + vp.width, pm.width); x++) {
      std::cout << color(pm.maps[frame][y][x]);
    }
    std::cout << std::endl;
  }
}

void play_animation(struct cppix::Viewport vp, struct cppix::PixelMap pm) {
  for (int t = 0, frame_num = pm.fps.size(); t < frame_num; t++) {
    draw_map(vp, pm, t);
    std::this_thread::sleep_for(
        std::chrono::duration<int, std::milli>(1000 / pm.fps[t]));
    std::cout << "\033[0;0H";
    std::cout << "\033[2J";
  }
}
} // namespace cppix
#endif

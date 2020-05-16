#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>

#define n2c(n)

struct RGB {
  char r;
  char g;
  char b;
};
std::string decode_color(char color_code) {
  std::string color_str;
  color_str = "";
  int cc;
  cc = (int)color_code;

  color_code += (char)(cc % 10 + 48);
  cc /= 10;
  color_str += (char)(cc % 10 + 48);
  cc /= 10;
  color_str += (char)(cc % 10 + 48);
  std::cout << color_str << std::endl;

  return color_str;
}
std::string color(struct RGB rgb) {
  return "\x1b[48;2;" + rgb.r + ";" + g + ";" + b + "m\u3000\x1b[0m";
}

int main(int argc, char **argv) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  printf("lines %d\n", w.ws_row);
  printf("columns %d\n", w.ws_col);

  char r;
  r = 135;

  std::vector<std::vector<struct RGB>> map;
  map.push_back(std::vector<struct RGB>());
  map[0].push_back({30, 200, 150});

  std::cout << color({2, 255, 100}) << std::endl;
  std::cout << color(map[0][0].r, map[0][0].g, map[0][0].b) << std::endl;
  std::cout << "\x1b[48;2;" << (int)r << ";"
            << "200"
            << ";"
            << "173"
            << "m\u3000\x1b[0m" << std::endl;
  return 0;
}

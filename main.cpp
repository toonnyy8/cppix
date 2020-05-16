#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

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

  color_str = (char)(cc % 10 + 48);
  cc /= 10;
  color_str = (char)(cc % 10 + 48) + color_str;
  cc /= 10;
  color_str = (char)(cc % 10 + 48) + color_str;

  return color_str;
}
std::string color(struct RGB rgb) {
  return "\x1b[48;2;" + decode_color(rgb.r) + ";" + decode_color(rgb.g) + ";" +
         decode_color(rgb.b) + "m\u3000\x1b[0m";
}

int main(int argc, char **argv) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  printf("lines %d\n", w.ws_row);
  printf("columns %d\n", w.ws_col);

  const int H = 10;
  const int W = 10;
  const int VH = 10;
  const int VW = 10;
  int offset_y;
  int offset_x;
  offset_y = 0;
  offset_x = 0;

  std::vector<std::vector<struct RGB>> map;

  for (int y = 0; y < H; y++) {
    map.push_back(std::vector<struct RGB>());
    for (int x = 0; x < W; x++) {
      map[y].push_back({(char)(x + y), (char)(10 * x), (char)(10 * y)});
    }
  }

  for (int y = offset_y; y < MIN(offset_y + VH, H); y++) {
    for (int x = offset_x; x < MIN(offset_x + VW, W); x++) {
      std::cout << color(map[y][x]);
    }
    std::cout << std::endl;
  }

  //  std::cout << "\033[0;0H\033[2J";

  return 0;
}

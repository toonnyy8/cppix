#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>

std::string color(std::string r, std::string g, std::string b) {
  return "\x1b[48;2;" + r + ";" + g + ";" + b + "m\u3000\x1b[0m";
}

int main(int argc, char **argv) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  printf("lines %d\n", w.ws_row);
  printf("columns %d\n", w.ws_col);

  std::cout << color("2", "255", "100") << std::endl;

  return 0;
}

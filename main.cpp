#include <ctype.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

std::string color(int r, int g, int b)
{
  return "\x1b[48;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + ";0m\u3000\x1b[0m";
}

int main(int argc, char **argv)
{
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  printf("lines %d\n", w.ws_row);
  printf("columns %d\n", w.ws_col);

  std::cout << color(2, 255, 100) << std::endl;
  return 0; // make sure your main returns int
}

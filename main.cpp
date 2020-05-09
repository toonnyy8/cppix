#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

// Regular background
#define BLKB "\e[40m"
#define REDB "\e[41m"
#define GRNB "\e[42m"
#define YELB "\e[43m"
#define BLUB "\e[44m"
#define MAGB "\e[45m"
#define CYNB "\e[46m"
#define WHTB "\e[47m"

// High intensty background
#define BLKHB "\e[0;100m"
#define REDHB "\e[0;101m"
#define GRNHB "\e[0;102m"
#define YELHB "\e[0;103m"
#define BLUHB "\e[0;104m"
#define MAGHB "\e[0;105m"
#define CYNHB "\e[0;106m"
#define WHTHB "\e[0;107"

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

int main(int argc, char **argv) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  printf("lines %d\n", w.ws_row);
  printf("columns %d\n", w.ws_col);

  printf("%sred\n", KRED);
  printf("%sgreen\n", KGRN);
  printf("%syellow\n", KYEL);
  printf("%sblue\n", KBLU);
  printf("%smagenta\n", KMAG);
  printf("%scyan\n", KCYN);
  printf("%swhite\n", KWHT);
  printf("%s \n", KNRM);

  printf("\033[031m bgColor is now red \033[047m And now white.\n");

  std::cout << ""
            << "\u3000";
  std::cout << YELB << "\u3000";
  return 0; // make sure your main returns int
}

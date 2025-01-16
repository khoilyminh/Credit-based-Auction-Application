#include "../libs/clearing.h"

#include <stdlib.h>

void clearing() {
#ifdef _WIN32
  system("cls");
#elif _WIN64
  system("cls");
#elif __APPLE__
  system("clear");
#elif __linux__
  std::system("clear");
#endif
}
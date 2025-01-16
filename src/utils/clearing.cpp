#include <stdlib.h>
#include "../libs/clearing.h"

void clearing()
{
#ifdef _WIN32
  system("cls");
#elif _WIN64
  system("cls");
#elif __APPLE__
  std::system("clear");
#elif __linux__
  std::system("clear");
#endif
}
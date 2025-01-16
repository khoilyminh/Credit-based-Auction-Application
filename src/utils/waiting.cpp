#include <iostream>
#include <fstream>

#ifdef _WIN32
#include <windows.h> // For Sleep on Windows
#elif _WIN64
#include <windows.h> // For Sleep on Windows
#elif __APPLE__
#include <unistd.h> // For sleep on Mac
#elif __linux__
#include <unistd.h> // For sleep on Linux
#endif

/** This function is used to sleep in cross OS. */
void waiting(int sleepTime)
{
#ifdef _WIN32
  Sleep(sleepTime * 1000);
#elif _WIN64
  Sleep(sleepTime * 1000);
#elif __APPLE__
  sleep(sleepTime);
#elif __linux__
  sleep(sleepTime);
#endif
}

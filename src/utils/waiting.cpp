#include <unistd.h>
#include <iostream>
#include <fstream>

/** This function is used to sleep in cross OS. */
void waiting(int sleepTime)
{
  // Read environment variable from ./data/environment file
  std::ifstream file("./data/environment", std::ios::in);
  std::string environment;
  std::getline(file, environment);
  file.close();

  if (environment == "WINDOWS")
    sleep(sleepTime * 1000);
  else
    sleep(sleepTime);
}

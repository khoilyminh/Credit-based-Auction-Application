#include <fstream>

#include "./libs/Dashboard.h"
#include "./libs/Auction.h"

int main(int argc, char *argv[])
{
  std::string environment = "NOT_WINDOWS";
  if (argc > 1)
  {
    environment = argv[1];
  }
  // Save the environment to a file
  std::ofstream file("./data/environment.txt", std::ios::trunc);
  file << environment;
  file.close();

  // Testing the Dashboard
  Dashboard dashboard;
  dashboard.displayMainMenu();

  return 0;
}
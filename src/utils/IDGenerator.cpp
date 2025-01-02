#include "../libs/IDGenerator.h"

#include <random>

/** This function is used to generate ASCII code of lowercase letter. */
int IDGenerator::generateLowercase() {
  std::random_device rd;
  std::mt19937 gen(rd());
  return std::uniform_int_distribution<int>(97, 122)(gen);
}

/** This function is used to generate ASCII code of uppercase letter. */
int IDGenerator::generateUppercase() {
  std::random_device rd;
  std::mt19937 gen(rd());
  return std::uniform_int_distribution<int>(65, 90)(gen);
}

/** This function is used to generate ASCII code of number. */
int IDGenerator::generateNumber() {
  std::random_device rd;
  std::mt19937 gen(rd());
  return std::uniform_int_distribution<int>(48, 57)(gen);
}

/** This function is used to generate a random string. */
std::string IDGenerator::generateID(int length = 16) {
  std::string raw;
  for (int time = 0; time < length; time++) {
    int type = rand() % 3;
    if (type == 0) {
      raw += generateLowercase();
    } else if (type == 1) {
      raw += generateUppercase();
    } else {
      raw += generateNumber();
    }
  }
  return raw;
}
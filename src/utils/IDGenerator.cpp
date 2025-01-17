#include "../libs/IDGenerator.h"

#include <random>

/** This function is used to generate ASCII code of lowercase letter. */
int IDGenerator::generateLowercase()
{
  return 97 + (std::rand() % (122 - 97 + 1));
}

/** This function is used to generate ASCII code of uppercase letter. */
int IDGenerator::generateUppercase()
{
  return 65 + (std::rand() % (90 - 65 + 1));
}

/** This function is used to generate ASCII code of number. */
int IDGenerator::generateNumber()
{
  return 48 + (std::rand() % (57 - 48 + 1));
}

/** This function is used to generate a random string. */
std::string IDGenerator::generateID(int length = 16)
{
  std::string raw;
  for (int time = 0; time < length; time++)
  {
    int type = rand() % 3;
    if (type == 0)
    {
      raw += char(generateLowercase());
    }
    else if (type == 1)
    {
      raw += char(generateUppercase());
    }
    else
    {
      raw += char(generateNumber());
    }
  }
  return raw;
}
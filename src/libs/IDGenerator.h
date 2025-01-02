#include <string>

class IDGenerator {
 private:
  /** This function is used to generate ASCII code of lowercase letter. */
  static int generateLowercase();
  /** This function is used to generate ASCII code of uppercase letter. */
  static int generateUppercase();
  /** This function is used to generate ASCII code of number. */
  static int generateNumber();

 public:
  /** This function is used to generate a random string. */
  static std::string generateID(int length);
};

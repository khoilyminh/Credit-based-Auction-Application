#include <iostream>

#include "./libs/Database.h"
#include "./libs/User.h"

int main() {
  User user = User("peterdinh", "12345678");
  Database database = Database();
  database.saveUser(&user);
  user.setPassword("87654321");
  database.saveUser(&user);
  return 0;
}
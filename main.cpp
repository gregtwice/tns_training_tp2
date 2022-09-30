#include <iostream>
#include <ostream>
#include <string>

#include "UserInterface.hpp"

void println(std::string str) { std::cout << str << std::endl; }

int main(int, char**) {
  auto cli = cli::UserInterface::getInstance();
  cli.loop();
}

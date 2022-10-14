#include "UserInterface.hpp"

int main(int, char**) {
  auto cli = cli::UserInterface::getInstance();
  cli.loop();
}

#include "Validator.hpp"

#include <iostream>
#include <algorithm>
#include <string>

namespace utils {

double Validator::validateDouble(std::string question, std::string errorMessage) {
  double x;
  while (1) {
    std::cout << question;
    if (std::cin >> x) {
      // valid number
      break;
    } else {
      // not a valid number
      std::cout << errorMessage + "\n";
      std::cin.clear();
      while (std::cin.get() != '\n')
        ;  // empty loop
    }
  }
  return x;
}

bool isASCII(const std::string& str) {
  return !std::any_of(str.begin(), str.end(), [](char c) {
    return static_cast<unsigned char>(c) > 127;
  });
}

bool containsSpaces(const std::string& str) {
  return std::any_of(str.begin(), str.end(), [](char c) {
    return static_cast<unsigned char>(c) == ' ';
  });
}

std::string Validator::validateASCIIString(std::string question,
  std::string errorMessage) {
  std::string userInput;

  while (1) {
    std::cout << question;
    std::getline(std::cin, userInput);

    if (containsSpaces(userInput) || !isASCII(userInput)) {
      std::cout << errorMessage + "\n";
      std::cin.clear();
      while (std::cin.get() != '\n')
        ;  // empty loop
    } else {
      break;
    }
  }
  return userInput;
}

}  // namespace utils

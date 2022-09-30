#ifndef SRC_UTILS_INCLUDE_VALIDATOR
#define SRC_UTILS_INCLUDE_VALIDATOR

#include <string>

namespace utils {
class Validator {
public:
  static double validateDouble(std::string question,
    std::string errorMessage);

  static std::string validateASCIIString(std::string question,
    std::string errorMessage = "Invalid Input !; Expected an ASCII string without spaces");
};

}  // namespace utils

#endif /* SRC_UTILS_INCLUDE_VALIDATOR */

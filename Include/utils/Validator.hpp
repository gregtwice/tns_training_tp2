#ifndef SRC_INCLUDE_UTILS_VALIDATOR
#define SRC_INCLUDE_UTILS_VALIDATOR

#include <string>

namespace utils {
class Validator {
public:
  /**
   * @brief Validates a double from user input
   * the function prints the question, then gets input from the 
   * 
   * @param question 
   * @param errorMessage 
   * @return double 
   */
  static double validateDouble(std::string question,
    std::string errorMessage);

  static std::string validateASCIIString(std::string question,
    std::string errorMessage = "Invalid Input !; Expected an ASCII string without spaces");
};

}  // namespace utils

#endif /* SRC_INCLUDE_UTILS_VALIDATOR */

#ifndef INCLUDE_CLI_OBSERVER
#define INCLUDE_CLI_OBSERVER

#include <string>

namespace cli {

class Observer {
public:
  /**
   * @brief method called by the subject to notify the observer of a change of state
   * 
   * @param message the string sent by the subject observed 
   */
  virtual void update(const std::string& message) = 0;
};

}  // namespace cli
#endif /* INCLUDE_CLI_OBSERVER */

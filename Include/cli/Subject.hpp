#ifndef INCLUDE_CLI_SUBJECT
#define INCLUDE_CLI_SUBJECT

#include "Observer.hpp"

namespace cli {

class Subject {
public:
  /**
   * @brief Adds an observer to the notification group
   * 
   * @param observer the observer to add
   */
  virtual void registerObserver(Observer* observer) = 0;

  /**
   * @brief Remove the observer from the notfication group
   * 
   * @param observer the observer to remove
   */
  virtual void removeObserver(Observer* observer) = 0;

  /**
   * @brief Sends a message to all the observers in the notification group
   */
  virtual void notifyObservers() = 0;
};
}  // namespace cli

#endif /* INCLUDE_CLI_SUBJECT */

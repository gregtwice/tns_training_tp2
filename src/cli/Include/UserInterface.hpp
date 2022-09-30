#ifndef SRC_CLI_INCLUDE_USERINTERFACE
#define SRC_CLI_INCLUDE_USERINTERFACE

#include "MyStaticVector.hpp"
#include "Point.hpp"

#include <memory>
#include <string>

namespace cli {

class UserInterface {
public:
  static UserInterface& getInstance() {
    static UserInterface instance;
    return instance;
  }
  /**
   * @brief Prints the munu of the user interface
   */
  void printMenu();
  /**
   * @brief Prints the menu and asks for user input, loops indefinitely
   */
  void loop();

private:
  enum class UserInterfaceState {
    MENU,
    CREATING,
  };

  mycollections::StaticVector<std::shared_ptr<planets::Point>, 20> objects;

  UserInterface() = default;
  /**
   * @brief Saves the current objects to a file chosen by the user
   */
  void handleSavingToFile();
  /**
   * @brief Loads the objects from a save file chosen by the user
   */
  void handleLoadingFromSaveFile();

  /**
   * @brief prints the menu to create an object
   */
  static void printCreatingMenu();
  /**
   * @brief prints the main menu of the application
   */
  void printMainMenu();

  /**
   * @brief Handles the user's input and acts accordingly by modifying the application's state
   */
  void handleInput();

  /**
   * @brief Asks for user input and returns it
   * @return the string input by the user
   */
  std::string readLine() const;
  UserInterfaceState state = UserInterfaceState::MENU;
};

}  // namespace cli

#endif /* SRC_CLI_INCLUDE_USERINTERFACE */

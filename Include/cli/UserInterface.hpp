#ifndef INCLUDE_CLI_USERINTERFACE
#define INCLUDE_CLI_USERINTERFACE

#include "MyStaticVector.hpp"
#include "Observer.hpp"
#include "Point.hpp"

#include <memory>
#include <string>

namespace cli {

class UserInterface : public cli::Observer {
public:
  /**
   * @brief Get the Singleton of the UserInterface
   * 
   * @return UserInterface& 
   */
  static UserInterface& getInstance() {
    static UserInterface instance;
    return instance;
  }

  /**
   * @brief Prints the munu of the user interface
   */
  void printMenu() const;

  /**
   * @brief Prints the menu and asks for user input, loops indefinitely
   */
  void loop();

  /**
   * @brief Prints a message from a planet
   */
  void update(const std::string&) override;

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
  void printCreatingMenu() const;
  /**
   * @brief prints the main menu of the application
   */
  void printMainMenu() const;

  /**
   * @brief Handles the user's input and acts accordingly by modifying the application's state
   */
  void handleInput();

  /**
   * @brief Asks for user input and returns it
   * @return the string input by the user
   */
  std::string readLine() const;
  UserInterfaceState _state = UserInterfaceState::MENU;
};

}  // namespace cli

#endif /* INCLUDE_CLI_USERINTERFACE */

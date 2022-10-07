#ifndef SRC_INCLUDE_CLI_USERINTERFACE
#define SRC_INCLUDE_CLI_USERINTERFACE

#include "MyStaticVector.hpp"
#include "Observer.hpp"
#include "Point.hpp"

#include <memory>
#include <string>

namespace cli {

class UserInterface : public cli::Observer {
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
   * @brief Runs the solar system in a separate thread for 50000 iterations
   */
  void runSolarSystem();

  /**
   * @brief Create a Small Solar System hardcoded in the application
   */
  void createSmallSolarSystem();

  /**
   * @brief Asks for user input and returns it
   * @return the string input by the user
   */
  std::string readLine() const;
  UserInterfaceState _state = UserInterfaceState::MENU;
};

}  // namespace cli

#endif /* SRC_INCLUDE_CLI_USERINTERFACE */

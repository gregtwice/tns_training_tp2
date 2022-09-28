#ifndef SRC_CLI_INCLUDE_USERINTERFACE
#define SRC_CLI_INCLUDE_USERINTERFACE

#include "MyStaticVector.hpp"
#include "Point.hpp"
#include "Sphere.hpp"
#include "Astre.hpp"

#include <memory>
#include <vector>

#include <string>

namespace cli {

class UserInterface {
public:
  static UserInterface& getInstance() {
    static UserInterface instance;
    return instance;
  }

  void printMenu();
  void loop();

private:
  enum class UserInterfaceState {
    MENU,
    CREATING,
  };

  mycollections::StaticVector<std::shared_ptr<planets::Point>, 20> objects;

  UserInterface(){};

  void handleSaving();
  void handleLoading();
  void printCreatingMenu();
  void printBaseMenu();
  void handleInput();

  std::string readLine();
  UserInterfaceState state = UserInterfaceState::MENU;
};

}  // namespace cli

#endif /* SRC_CLI_INCLUDE_USERINTERFACE */

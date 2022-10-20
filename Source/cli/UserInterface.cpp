#include "UserInterface.hpp"

#include <algorithm>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <regex>
#include <sstream>
#include <chrono>
#include <ctime>
#include <string>
#include <thread>
#include <cstdio>
#include <cstdlib>

#include "Asteroid.hpp"
#include "MyStaticVector.hpp"
#include "Position.hpp"
#include "Point.hpp"
#include "SolarSystem.hpp"
#include "Sphere.hpp"
#include "Astre.hpp"
#include "Planet.hpp"

#include "Validator.hpp"

namespace cli {

namespace mmc {
enum class MainMenuChoice {
  INVALID,
  PRINT,
  CREATE,
  SAVE,
  LOAD,
  SIMULATE,
  QUIT,
};

MainMenuChoice fromInt(int choice) {
  switch (choice) {
    case 1:
      return MainMenuChoice::PRINT;
    case 2:
      return MainMenuChoice::CREATE;
    case 3:
      return MainMenuChoice::SAVE;
    case 4:
      return MainMenuChoice::LOAD;
    case 5:
      return MainMenuChoice::SIMULATE;
    case 6:
      return MainMenuChoice::QUIT;
    default:
      return MainMenuChoice::INVALID;
  }
}
}  // namespace mmc
namespace cmc {
enum class CreateMenuChoice {

  INVALID,
  POINT,
  SPHERE,
  ASTRE,
  QUIT,
};
CreateMenuChoice fromInt(int choice) {
  switch (choice) {
    case 1:
      return CreateMenuChoice::POINT;
    case 2:
      return CreateMenuChoice::SPHERE;
    case 3:
      return CreateMenuChoice::ASTRE;
    case 4:
      return CreateMenuChoice::QUIT;
    default:
      return CreateMenuChoice::INVALID;
  }
}
}  // namespace cmc

void UserInterface::printCreatingMenu() const {
  std::cout << "\n======Object Creation======\n\t"
            << "1) Point \n\t"
            << "2) Sphere\n\t"
            << "3) Astre\n\t"
            << "4) Go back\n";
}

std::string UserInterface::readLine() const {
  std::string userInput;
  std::cout << ">>> ";
  std::cin >> userInput;
  return userInput;
}

template <class T>
static void printIterator(T iter) {
  iter.forEach([](auto v) { std::cout << *v << "\n"; });
}

void UserInterface::handleSavingToFile() {
  std::filesystem::path saveFilePath = ".";

  std::string fileName = utils::Validator::validateASCIIString("What is the name of the file you want to save to? \n>>>");

  std::cout << "\"" + fileName + ".psf\"";
  saveFilePath /= (fileName + ".psf");

  std::ofstream saveFileHandle(saveFilePath);

  objects.iter().forEach([&](auto obj) { saveFileHandle << *obj << "\n"; });

  saveFileHandle.close();
}

void runSystem(mycollections::StaticVector<planets::Planet*, 40> bodies) {
  // std::this_thread::sleep_for(1ms);

  std::cout << "Ended simulation\n";
}

/**
 * @brief Function to convert a date to a time_t that can the be formated
*/
template <typename TP>
std::time_t to_time_t(TP tp) {
  using namespace std::chrono;
  auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now() + system_clock::now());
  return system_clock::to_time_t(sctp);
}

void UserInterface::handleLoadingFromSaveFile() {
  namespace fs = std::filesystem;
  fs::path workingDir = fs::current_path();

  // List the current directory for save files.

  std::stringstream ss;

  for (fs::directory_entry entry : fs::directory_iterator(workingDir)) {
    if (entry.path().extension() == ".psf") {
      std::wstringstream wss;
      auto wd = to_time_t(entry.last_write_time());
      std::tm tm = *std::localtime(&wd);
      ss << "\t" + entry.path().filename().string() << " Last modified: ";
      ss << std::put_time(&tm, "%F %T") << "\n";
    }
  }
  if (ss.str().empty()) {
    std::cout << "No Save files were found in the current directory\n";
  } else {
    std::cout << "The following save files were found in the current directory:\n";
    std::cout << ss.str();
  }

  std::string saveFileName = utils::Validator::validateASCIIString("Please input the name of the file you want to load\n>>>");

  std::ifstream infile("./" + saveFileName);
  std::string line;

  std::regex pointRx(planets::Point::savePattern);
  std::regex sphereRx(planets::Sphere::savePattern);
  std::regex astreRx(planets::Astre::savePattern);
  std::regex planetRx(planets::Planet::savePattern);
  std::smatch smatch;

  while (std::getline(infile, line)) {
    std::cout << line << "\n";
    if (std::regex_match(line, smatch, pointRx)) {
      objects.push(std::make_shared<planets::Point>(line));
    } else if (std::regex_match(line, smatch, sphereRx)) {
      objects.push(std::make_shared<planets::Sphere>(line));
    } else if (std::regex_match(line, smatch, astreRx)) {
      objects.push(std::make_shared<planets::Astre>(line));
    } else if (std::regex_match(line, smatch, planetRx)) {
      objects.push(std::make_shared<planets::Planet>(line));
    }
  }
}

void UserInterface::handleInput() {
  auto userInput = readLine();
  int userChoice;
  try {
    userChoice = std::stoi(userInput);
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
  auto choice = mmc::fromInt(userChoice);
  switch (_state) {
    case UserInterfaceState::MENU:
      switch (choice) {
          // print the object in the system created by the user
        case mmc::MainMenuChoice::PRINT: {
          auto pointIterator = objects.iter();
          printIterator(pointIterator);
        } break;
        // create space objects
        case mmc::MainMenuChoice::CREATE:
          _state = UserInterfaceState::CREATING;
          break;

        // Save the current system to a file
        case mmc::MainMenuChoice::SAVE:
          handleSavingToFile();
          break;

          // load a system saved to disk from a file
        case mmc::MainMenuChoice::LOAD:
          handleLoadingFromSaveFile();
          break;

          // quit
        case mmc::MainMenuChoice::QUIT:
          _shouldExit = true;
          break;

          // simulate the hardcoded system
        case mmc::MainMenuChoice::SIMULATE: {
          if (objects.getSize() > 0) {
            planets::SolarSystem sol(objects.iter());
            std::thread solSys(&planets::SolarSystem::run, sol, 50000);
            solSys.detach();
          } else {
            planets::SolarSystem sol;
            std::thread solSys(&planets::SolarSystem::run, sol, 50000);
            solSys.detach();
          }
        }
        default:
          std::cerr << "not a valid input !!!"
                    << "\n";
          break;
      }
      break;

    case UserInterfaceState::CREATING: {
      auto choice = cmc::fromInt(userChoice);
      switch (choice) {
        case cmc::CreateMenuChoice::POINT: {
          std::string n = "Autogenerated";
          planets::Point p = planets::Point(n, planets::Position(1, 2, 3));
          objects.push(std::make_shared<planets::Point>(p));
          break;
        }
        case cmc::CreateMenuChoice::SPHERE: {
          planets::Sphere s = planets::Sphere::sphereFromUserInput();
          objects.push(std::make_shared<planets::Sphere>(s));
          break;
        }
        case cmc::CreateMenuChoice::ASTRE: {
          auto a = planets::Astre::astreFromUserInput();
          objects.push(std::make_shared<planets::Astre>(a));
          break;
        }
        case cmc::CreateMenuChoice::QUIT:
          _state = UserInterfaceState::MENU;
          break;
        default:
          break;
      }
    } break;

    default:
      break;
  }
}

void UserInterface::loop() {
  while (!_shouldExit) {
    printMenu();
    handleInput();
  }
}

void UserInterface::printMainMenu() const {
  std::cout << "\n======Planet Calculator=====" << std::endl;
  std::cout << "Select an action :\n\t"
            << "1) List all objects\n\t"
            << "2) Create an object\n\t"
            << "3) Save the current objects\n\t"
            << "4) Load a save of a previous context\n\t"
            << "5) Lanch solar system in a thread\n\t"
            << "6) Quit\n";
}

void UserInterface::printMenu() const {
  switch (_state) {
    case UserInterfaceState::MENU:
      printMainMenu();
      break;
    case UserInterfaceState::CREATING:
      printCreatingMenu();
      break;
    default:
      break;
  }
}
void UserInterface::update(const std::string& message) {
  std::cout << message << "\n";
}

}  // namespace cli
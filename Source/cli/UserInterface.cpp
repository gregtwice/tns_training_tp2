#include "UserInterface.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <filesystem>
#include <regex>
#include <sstream>
#include <chrono>
#include <ctime>
#include <string>
#include <thread>

#include "MyStaticVector.hpp"
#include "Position.hpp"
#include "Point.hpp"
#include "Sphere.hpp"
#include "Astre.hpp"
#include "Planet.hpp"

#include "Validator.hpp"

namespace cli {

void UserInterface::printCreatingMenu() {
  std::cout << "\n======Object Creation======\n\t"
            << "1) Point \n\t"
            << "2) Sphere\n\t"
            << "3) Astre\n\t"
            << "4) Go back\n";
}

std::string UserInterface::readLine() const {
  std::string userInput;
  std::cout << ">>> ";
  std::getline(std::cin, userInput);
  return userInput;
}

template <class T>
static void printIterator(T iter) {
  while (iter.hasNext()) {
    auto val = iter.next();
    std::cout << *val << std::endl;
  }
}

void UserInterface::handleSavingToFile() {
  std::filesystem::path saveFilePath = ".";

  std::string fileName = utils::Validator::validateASCIIString("What is the name of the file you want to save to? \n>>>");

  std::cout << "\"" + fileName + ".psf\"";
  saveFilePath /= (fileName + ".psf");

  std::ofstream saveFileHandle(saveFilePath);

  auto iter = objects.iter();
  while (iter.hasNext()) {
    auto obj = iter.next();
    saveFileHandle << *obj << "\n";
  }
  saveFileHandle.close();
}

void runSystem(mycollections::StaticVector<planets::Planet*, 20> bodies) {
  using namespace std::chrono_literals;
  for (int i = 0; i < 50000; i++) {
    for (size_t j = 0; j < bodies.getSize(); j++) {
      bodies[j]->updateVelocity(bodies.iter(), 1);
    }
    for (size_t j = 0; j < bodies.getSize(); j++) {
      bodies[j]->updatePosition(1);
    }
    std::this_thread::sleep_for(1ms);
  }
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
  std::smatch smatch;

  while (std::getline(infile, line)) {
    std::cout << line;
    if (std::regex_match(line, smatch, pointRx)) {
      std::cout << "Point ??\n";
      objects.push(std::make_shared<planets::Point>(line));
    } else if (std::regex_match(line, smatch, sphereRx)) {
      objects.push(std::make_shared<planets::Sphere>(line));
    } else if (std::regex_match(line, smatch, astreRx)) {
      objects.push(std::make_shared<planets::Astre>(line));
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

  switch (_state) {
    case UserInterfaceState::MENU:
      switch (userChoice) {
        case 1: {
          auto pointIterator = objects.iter();
          printIterator(pointIterator);
        } break;
        case 2:
          _state = UserInterfaceState::CREATING;
          break;
        case 3:
          handleSavingToFile();
          break;
        case 4:
          handleLoadingFromSaveFile();
          break;
        case 5:
          exit(0);
          break;
        case 6: {
          mycollections::StaticVector<planets::Planet*, 20> bodies;
          for (size_t j = 0; j < objects.getSize(); j++) {
            std::shared_ptr<planets::Planet> p;
            p = std::dynamic_pointer_cast<planets::Planet>(objects[j]);
            bodies.push(p.get());
          }
          std::thread sol(runSystem, bodies);
          sol.detach();
        }
        default:
          std::cerr << "not a valid input !!!"
                    << "\n";
          break;
      }
      break;
    case UserInterfaceState::CREATING:
      switch (userChoice) {
        case 1: {
          std::string n = "Autogenerated";
          planets::Point p = planets::Point(n, planets::Position(1, 2, 3));
          objects.push(std::make_shared<planets::Point>(p));
          break;
        }
        case 2: {
          planets::Sphere s = planets::Sphere::sphereFromUserInput();
          objects.push(std::make_shared<planets::Sphere>(s));
          break;
        }
        case 3: {
          auto a = planets::Astre::astreFromUserInput();
          objects.push(std::make_shared<planets::Astre>(a));
          break;
        }
        case 4:
          _state = UserInterfaceState::MENU;
          break;
        default:
          break;
      }
      break;

    default:
      break;
  }
}

void UserInterface::loop() {
  createSmallSolarSystem();
  while (true) {
    printMenu();
    handleInput();
  }
}

void UserInterface::printMainMenu() {
  std::cout << "\n======Planet Calculator=====" << std::endl;
  std::cout << "Select an action :\n\t"
            << "1) List all objects\n\t"
            << "2) Create an object\n\t"
            << "3) Save the current objects\n\t"
            << "4) Load a save of a previous context\n\t"
            << "5) Quit\n"
            << "6) Lanch solar system in a thread\n";
}

void UserInterface::printMenu() {
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

void UserInterface::createSmallSolarSystem() {
  using namespace planets;

  Point sun_p = Point("Sun", Position(0, 0, 0));
  Sphere sun_s(sun_p, 1500 * 2);
  Astre sun_a = Astre(sun_s, (50 * sun_s.getDiameter() / 2 * sun_s.getDiameter() / 2 / Astre::gravitationnalConstantModel) / sun_s.getVolume());
  Planet sun(sun_a, Vec3(0, 0, 0));

  Point earth_p = Point("Earth", Position(-11033.0, 0.0, 0.0));
  Sphere earth_s(earth_p, 300 * 2);
  Astre earth_a = Astre(earth_s, earth_s.getVolume());
  earth_a.setMass((10 * earth_s.getDiameter() / 2 * earth_s.getDiameter() / 2 / Astre::gravitationnalConstantModel));
  Planet earth1(earth_a, Vec3(0, 102.57, 0));
  Planet earth2(earth_a, Vec3(0, 102.57, 0));

  earth2.setPosition(Position(-13038, 0, 0));
  earth2.setVelocity(Vec3(0, 80.6, 0));
  earth1.setVelocity(Vec3(0, 115.3, 0));
  earth1.setName("Earth 1");
  earth2.setName("Earth 2");

  Point far_away_p = Point("far_away", Position(-24295, 0, 0));
  Sphere far_away_s(far_away_p, 400);
  Astre far_away_a = Astre(far_away_s, 7.342e22 / far_away_s.getVolume());
  far_away_a.setMass((8 * far_away_a.getDiameter() / 2 * far_away_a.getDiameter() / 2 / Astre::gravitationnalConstantModel));
  Planet far_away(far_away_a, Vec3(0, 70.23, 0));

  Point sat_p("Green Satelite", Position(-23549, 0, 0));
  Sphere sat_s(sat_p, 50 * 2);
  Astre sat_a(sat_s, 0);
  sat_a.setMass((3 * sat_a.getDiameter() / 2 * sat_a.getDiameter() / 2 / Astre::gravitationnalConstantModel));
  Planet sat(sat_a, Vec3(0, 51, 0));

  Point pgg_p("Purple gas giant", Position(-58811, 0, 0));  //49811

  Sphere pgg_s(pgg_p, 500 * 2);
  Astre pgg_a(pgg_s, 0);
  pgg_a.setMass((14 * pgg_a.getDiameter() / 2 * pgg_a.getDiameter() / 2 / Astre::gravitationnalConstantModel));
  Planet pgg(pgg_a, Vec3(0, 50.3, 0));

  Point pggs1_p("Purple gas giant sat1", Position(-55700, 0, 0));
  Sphere pggs1_s(pggs1_p, 40 * 2);
  Astre pggs1_a(pggs1_s, 0);
  pggs1_a.setMass((2 * pggs1_a.getDiameter() / 2 * pggs1_a.getDiameter() / 2 / Astre::gravitationnalConstantModel));
  Planet pggs1(pggs1_a, Vec3(0, 18.3, 0));

  objects.push(std::make_shared<Planet>(earth1));
  objects.push(std::make_shared<Planet>(earth2));
  objects.push(std::make_shared<Planet>(sun));
  objects.push(std::make_shared<Planet>(sat));
  objects.push(std::make_shared<Planet>(pgg));
  objects.push(std::make_shared<Planet>(pggs1));
  objects.push(std::make_shared<Planet>(far_away));

  auto it = objects.iter();
  while (it.hasNext()) {
    std::shared_ptr<Planet> p;
    p = std::dynamic_pointer_cast<Planet>(it.next());
    p->registerObserver(this);
  }
  // it = objects.iter();
  // while (it.hasNext()) {
  //   std::shared_ptr<Planet> p;
  //   p = std::dynamic_pointer_cast<Planet>(it.next());
  //   p->notifyObservers();
  // }
}

void UserInterface::runSolarSystem() {
}

}  // namespace cli
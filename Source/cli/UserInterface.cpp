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
  std::cin >> userInput;
  return userInput;
}

template <class T>
static void printIterator(T iter) {
  // auto here but will try to understand how it works
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

void runSystem(mycollections::StaticVector<planets::Planet*, 20> bodies) {
  using namespace std::chrono_literals;
  for (int i = 0; i < 50000; i++) {
    bodies
      .iter()
      .forEach([&](planets::Planet* body) { body->updateVelocity(bodies.iter(), 1); })
      .forEach([&](planets::Planet* body) { body->updatePosition(1); });
    // std::this_thread::sleep_for(1ms);
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
            << "5) Quit\n\t"
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

  auto sun_radius = 1500.0;
  auto sun_position = Position(0, 0, 0);
  auto sun_surface_gravity = 50;
  auto sun_mass = (sun_surface_gravity * sun_radius * sun_radius / Astre::gravitationnalConstantModel);

  Planet sun(Astre(Sphere(Point("Sun", sun_position), sun_radius * 2), sun_surface_gravity), Vec3(0, 0, 0));
  sun.setMass(sun_mass);

  /**********************************************************************************************/

  auto earth1_position = Position(-11033, 0, 0);
  auto earth2_position = Position(-13038, 0, 0);
  auto earth1_speed = Vec3(0, 115.3, 0);
  auto earth2_speed = Vec3(0, 80.6, 0);

  auto earth_radius = 300;
  auto earth_surface_gravity = 10;
  auto earth_speed = Vec3(0, 102.57, 0);
  auto earth_mass = (earth_surface_gravity * earth_radius * earth_radius / Astre::gravitationnalConstantModel);

  Planet earth1(Astre(Sphere(Point("Earth 1", earth1_position), earth_radius * 2), 0), earth1_speed);
  Planet earth2(Astre(Sphere(Point("Earth 2", earth2_position), earth_radius * 2), 0), earth2_speed);
  earth1.setMass(earth_mass);
  earth2.setMass(earth_mass);

  /**********************************************************************************************/

  auto gp_position = Position(-24295, 0, 0);
  auto gp_radius = 200;
  auto gp_surface_gravity = 8;
  auto gp_mass = (gp_surface_gravity * gp_radius * gp_radius / Astre::gravitationnalConstantModel);

  Planet green_planet(Astre(Sphere(Point("Green Planet", gp_position), gp_radius * 2), gp_surface_gravity), Vec3(0, 70.23, 0));
  green_planet.setMass(gp_mass);

  /**********************************************************************************************/

  auto gp_sat_position = Position(-23549, 0, 0);
  auto gp_sat_radius = 50;
  auto gp_sat_surface_gravity = 3;
  auto gp_sat_mass = gp_sat_surface_gravity * gp_sat_radius * gp_sat_radius / Astre::gravitationnalConstantModel;

  Planet gp_sat(Astre(Sphere(Point("Green Planet Satelite", gp_sat_position), gp_sat_radius * 2), 0), Vec3(0, 51, 0));
  gp_sat.setMass(gp_sat_mass);

  auto pgg_position = Position(-58811, 0, 0);
  auto pgg_radius = 500;
  auto pgg_surface_gravity = 14;
  auto pgg_mass = pgg_surface_gravity * pgg_radius * pgg_radius / Astre::gravitationnalConstantModel;

  Planet pgg(Astre(Sphere(Point("Purple gas giant", pgg_position), pgg_radius * 2), 0), Vec3(0, 50.3, 0));
  pgg.setMass(pgg_mass);
  /**********************************************************************************************/
  auto pgg_sat_radius = 40;
  auto pgg_sat_position = Position(-55700, 0, 0);
  auto pgg_sat_surface_gravity = 2;
  auto pgg_sat_mass = (pgg_sat_surface_gravity * pgg_sat_radius * pgg_sat_radius / Astre::gravitationnalConstantModel);

  Planet pgg_sat(Astre(Sphere(Point("Purple gas giant sat1", pgg_sat_position), pgg_sat_radius * 2), 0), Vec3(0, 18.3, 0));
  pgg_sat.setMass(pgg_mass);

  objects.push(std::make_shared<Planet>(std::move(earth1)));
  objects.push(std::make_shared<Planet>(std::move(earth2)));
  objects.push(std::make_shared<Planet>(std::move(sun)));
  objects.push(std::make_shared<Planet>(std::move(gp_sat)));
  objects.push(std::make_shared<Planet>(std::move(pgg)));
  objects.push(std::make_shared<Planet>(std::move(pgg_sat)));
  objects.push(std::make_shared<Planet>(std::move(green_planet)));

  objects
    .iter()
    .forEach([this](std::shared_ptr<Point> x) {
      std::shared_ptr<Planet> p;
      p = std::dynamic_pointer_cast<Planet>(x);
      p->registerObserver(this);
    })
    .forEach([](std::shared_ptr<Point> x) {
      std::shared_ptr<Planet> p;
      p = std::dynamic_pointer_cast<Planet>(x);
      p->notifyObservers();
    });
}

}  // namespace cli
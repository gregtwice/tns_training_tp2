#ifndef INCLUDE_PLANETS_STAR_HPP

#include "Astre.hpp"

namespace planets {
/**
 * The star Class behaves like an astre without having a velocity, 
 * thus making it fixed in the simulation
 * 
 */
class Star : public Astre {
public:
  Star();

private:
};

}  // namespace planets

#endif  // !INCLUDE_PLANETS_STAR_HPP

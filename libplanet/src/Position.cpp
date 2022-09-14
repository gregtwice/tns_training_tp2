#include "Position.hpp"

namespace planets {

Position::Position(double x, double y, double z) : _x(x), _y(y), _z(z) {}
Position::~Position() = default;

}  // namespace planets
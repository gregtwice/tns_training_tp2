#pragma once

namespace libPlanet {

class Position {  // could be a struct
   public:
    double _x;
    double _y;
    double _z;
    /**
     * @brief Construct a new Position object
     *
     * @param x the X coordinate
     * @param y the Y coordinate
     * @param z the Z coordinate
     */
    Position(double x, double y, double z);
    ~Position();
};
}  // namespace libPlanet

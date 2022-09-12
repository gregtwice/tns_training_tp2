#pragma once

#include "Point.h"
#include "Sphere.h"

namespace libPlanet {
class Astre : public Sphere {
   private:
    double _density;

   public:
    /**
     * @brief Construct a new Astre object
     *
     * @param sphere a sphere upon which the Astre will be based
     * @param density the Astre's density
     */
    Astre(Sphere sphere, double density);

    /**
     * @brief Construct a new Astre object
     *
     * @param point a Point upon which the Astre will be based
     * @param diameter the diameter of the Astre
     * @param density  the density of the Astre
     */
    Astre(Point point, double diameter, double density);
    ~Astre() = default;

    /**
     * @brief Returns the computed mass of the Astre
     *
     * @return the mass
     */
    double getMass();

    /**
     * @brief Get the Density of the sphere
     *
     * @return the density
     */
    double getDensity();

    bool operator==(Sphere&);
    bool operator<=(Sphere&);
    bool operator>=(Sphere&);
    bool operator>(Sphere&);
    bool operator<(Sphere&);

    bool operator==(Astre&);
    bool operator<=(Astre&);
    bool operator>=(Astre&);
    bool operator>(Astre&);
    bool operator<(Astre&);
};

}  // namespace libPlanet
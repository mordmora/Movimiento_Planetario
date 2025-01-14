#ifndef PLANET_HPP
#define PLANET_HPP

#include <string>
#include "vector2D.hpp"

class Planet {
    public:
    
    Planet(const std::string name, const double mass
        ,const  math_op::Vector2D<double> &position
        ,const math_op::Vector2D<double> &velocity) : name(name), mass(mass), position(position), velocity(velocity) {}

    std::string name;
    double mass;
    math_op::Vector2D<double> position;
    math_op::Vector2D<double> velocity;
};

#endif
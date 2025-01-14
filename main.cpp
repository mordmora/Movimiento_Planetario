#include "vector2D.hpp"
#include "simulation.hpp"
#include "planet.hpp"
#include <iostream>
#include <windows.h>

int main(){

    Simulation sim(360000); // 1 hora = 3600

    sim.add_planet(Planet(std::string("Tierra"), 5.972e24, math_op::Vector2D<double>(0, 1.496e11), math_op::Vector2D<double>(29780, 0)));
    //sim.add_planet(Planet(std::string("Marte"), 5.972e24, math_op::Vector2D<double>(0, 2.496e11), math_op::Vector2D<double>(2954, 0)));
    sim.add_planet(Planet(std::string("Sol"), 1.989e30, math_op::Vector2D<double>(0,0), math_op::Vector2D<double>(0, 0)));

    for(int i = 0; i < 200; i++){
        sim.update();
        sim.draw();
        Sleep(50);
    }

    return 1;

}

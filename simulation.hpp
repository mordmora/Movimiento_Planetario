#ifndef SIMULATION_HPP
#define SIMULATION_HPP


#include "planet.hpp"
#include "vector2D.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include<windows.h>
#define G 6.67430e-11

class Simulation {

private:
    std::vector<Planet> planets;
    double time_step;
    static const int VIEW_WIDTH = 80; 
    static const int VIEW_HEIGHT = 40;  
    double scale;
    bool show_data = false;

public:
    explicit Simulation(double time_step) : time_step(time_step) {
        // 1 AU ≈ 1.496e11m
        scale = 1.496e11 / (VIEW_HEIGHT/4);
    }

    void add_planet(const Planet& planet) {
        planets.push_back(planet);
    }


    void update() {
        std::vector<math_op::Vector2D<double>> accelerations(planets.size(), math_op::Vector2D<double>(0, 0));
        for (size_t i = 0; i < planets.size(); i++) {
            if (planets[i].name == "Sol") continue;

            for (size_t j = 0; j < planets.size(); j++) {
                if (i == j) continue;

                math_op::Vector2D<double> direction = planets[j].position - planets[i].position;
                double distance = direction.get_magnitude();
                if (distance < 1e-10) continue;

                double force = G * planets[i].mass * planets[j].mass / (distance * distance);
                math_op::Vector2D<double> acceleration = direction.normalize() * (force / planets[i].mass);
                accelerations[i] = accelerations[i] + acceleration;
            }
        }

        for (size_t i = 0; i < planets.size(); i++) {
            if (planets[i].name == "Sol") continue;

            planets[i].velocity = planets[i].velocity + accelerations[i] * time_step;
            planets[i].position = planets[i].position + planets[i].velocity * time_step;
        }
    }


    void printState() const {
        for (const auto& planet : planets) {
            std::cout << std::fixed << std::setprecision(2);
            std::cout << planet.name << " - Position: (" << planet.position.x << ", " << planet.position.y
                << ") Velocity: (" << planet.velocity.x << ", " << planet.velocity.y << ")\n";
        }
        std::cout << "------------------------------------------\n";
    }

    void draw() const {
        std::vector<std::vector<char>> grid(VIEW_HEIGHT, std::vector<char>(VIEW_WIDTH, ' '));

        for(int i = 0; i < VIEW_WIDTH; i++) {
            grid[0][i] = '-';
            grid[VIEW_HEIGHT-1][i] = '-';
        }
        for(int i = 0; i < VIEW_HEIGHT; i++) {
            grid[i][0] = '|';
            grid[i][VIEW_WIDTH-1] = '|';
        }
        
        int centerX = VIEW_WIDTH / 2;
        int centerY = VIEW_HEIGHT / 2;

        grid[centerY][centerX] = '+';

        for(const auto& planet : planets) {

            int x = centerX + static_cast<int>(planet.position.x / scale);

            int y = centerY - static_cast<int>(planet.position.y / scale);

            x = std::max(0, std::min(x, VIEW_WIDTH-1));
            y = std::max(0, std::min(y, VIEW_HEIGHT-1));

            char symbol = (planet.name == "Sol") ? '*' : 'o';
            grid[y][x] = symbol;

            if(show_data) std::cout << planet.name 
                     << "\nScale: " << scale
                     << "\nReal pos: (" << planet.position.x << "," << planet.position.y << ")"
                     << "\nGrid pos before clamp: (" 
                     << centerX + static_cast<int>(planet.position.x / scale) << "," 
                     << centerY - static_cast<int>(planet.position.y / scale) << ")"
                     << "\nFinal grid pos: (" << x << "," << y << ")\n\n";
        }
        //Sleep(300);
        system("cls");
        for(const auto& row : grid) {
            for(char cell : row) {
                std::cout << cell;
            }
            std::cout << '\n';
        }
        
    }

};

#endif
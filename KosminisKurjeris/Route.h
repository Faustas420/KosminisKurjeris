#pragma once
#include <string>

struct Route {
    std::string destination;
    int fuelCost;
    int riskPercent;
    int bonusFuel;

    Route(const std::string& dest, int fuel, int risk, int bonus = 0)
        : destination(dest), fuelCost(fuel), riskPercent(risk), bonusFuel(bonus) {
    }
};

#include "Planet.h"
#include <iostream>

Planet::Planet(const std::string& planetName, bool station)
    : name(planetName), hasSpaceStation(station) {}

const std::string& Planet::getName() const { return name; }
bool Planet::hasStation() const { return hasSpaceStation; }

std::vector<Route>& Planet::getRoutes() { return availableRoutes; }
const std::vector<Route>& Planet::getRoutes() const { return availableRoutes; }

void Planet::addRoute(const std::string& dest, int fuel, int risk, int bonus) {
    availableRoutes.emplace_back(dest, fuel, risk, bonus);
}

size_t Planet::getRouteCount() const { return availableRoutes.size(); }

void Planet::displayRoutes() const {
    std::cout << "\nRoutes from " << name << ":\n";
    int idx = 1;
    for (const auto& route : availableRoutes) {
        std::cout << idx++ << ") "
                  << route.destination
                  << " | Fuel: " << route.fuelCost
                  << " | Risk: " << route.riskPercent << "%";
        if (route.bonusFuel > 0)
            std::cout << " | Bonus fuel: " << route.bonusFuel;
        std::cout << "\n";
    }
}

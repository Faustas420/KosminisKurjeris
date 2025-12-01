#include "GameMap.h"
#include <iostream>

GameMap::GameMap(std::unique_ptr<IMapStrategy> mapStrategy)
    : strategy(std::move(mapStrategy)) {
    strategy->buildMap(planets);
}

std::string GameMap::getGoal() const { return strategy->getGoalPlanet(); }
std::string GameMap::getStartPlanet() const { return strategy->getStartPlanet(); }

Planet* GameMap::findPlanet(const std::string& name) {
    for (auto& planet : planets) {
        if (planet.getName() == name)
            return &planet;
    }
    return nullptr;
}

void GameMap::displayMap() const {
    std::cout << "\n=== MAP ===\n";
    std::cout << "Start: " << getStartPlanet() << "\n";
    std::cout << "Goal: " << getGoal() << "\n";
    std::cout << "Planets:\n";

    for (const auto& planet : planets) {
        std::cout << "- " << planet.getName();
        if (planet.hasStation())
            std::cout << " (Station)";
        std::cout << "\n";

        const auto& routes = planet.getRoutes();
        for (const auto& r : routes) {
            std::cout << "   -> " << r.destination
                << " | Fuel: " << r.fuelCost
                << " | Risk: " << r.riskPercent << "%";
            if (r.bonusFuel > 0)
                std::cout << " | Bonus: " << r.bonusFuel;
            std::cout << "\n";
        }
    }
    std::cout << "=== END MAP ===\n";
}

std::vector<Planet>& GameMap::getPlanets() { return planets; }

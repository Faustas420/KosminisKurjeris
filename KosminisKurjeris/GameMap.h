#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Planet.h"
#include "IMapStrategy.h"

class GameMap {
private:
    std::vector<Planet> planets;
    std::unique_ptr<IMapStrategy> strategy;

public:
    GameMap(std::unique_ptr<IMapStrategy> mapStrategy);

    std::string getGoal() const;
    std::string getStartPlanet() const;
    Planet* findPlanet(const std::string& name);
    void displayMap() const;

    std::vector<Planet>& getPlanets();

    
    IMapStrategy* getStrategy() const { return strategy.get(); }
};

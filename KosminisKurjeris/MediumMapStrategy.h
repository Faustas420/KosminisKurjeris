#pragma once
#include "IMapStrategy.h"
#include "Planet.h"
#include <vector>
#include <string>

class MediumMapStrategy : public IMapStrategy {
public:
    void buildMap(std::vector<Planet>& planets) override;
    std::string getGoalPlanet() const override;
    std::string getStartPlanet() const override;
    std::string getMapDescription() const override;
};

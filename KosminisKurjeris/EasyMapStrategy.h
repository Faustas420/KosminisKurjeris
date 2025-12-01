#pragma once
#include "IMapStrategy.h"

class EasyMapStrategy : public IMapStrategy {
public:
    void buildMap(std::vector<Planet>& planets) override;
    std::string getGoalPlanet() const override { return "Neptune"; }
    std::string getStartPlanet() const override { return "Earth"; }
    std::string getMapDescription() const override { return "Easy map"; }
};

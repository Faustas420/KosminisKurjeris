#pragma once
#include <vector>
#include <string>
class Planet; 

class IMapStrategy {
public:
    virtual void buildMap(std::vector<Planet>& planets) = 0;
    virtual std::string getGoalPlanet() const = 0;
    virtual std::string getStartPlanet() const = 0;
    virtual std::string getMapDescription() const = 0;
    virtual ~IMapStrategy() = default;
};

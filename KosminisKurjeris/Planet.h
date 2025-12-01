#pragma once
#include <string>
#include <vector>
#include "Route.h"

class Planet {
private:
    std::string name;
    bool hasSpaceStation;
    std::vector<Route> availableRoutes;

public:
    Planet(const std::string& n, bool station = false);

    const std::string& getName() const;
    bool hasStation() const;

    void addRoute(const std::string& dest, int fuel, int risk, int bonus = 0);

    std::vector<Route>& getRoutes();
    const std::vector<Route>& getRoutes() const;

    size_t getRouteCount() const;

    void displayRoutes() const;
};

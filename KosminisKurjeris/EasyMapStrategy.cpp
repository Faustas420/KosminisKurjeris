#include "EasyMapStrategy.h"
#include "Planet.h"

void EasyMapStrategy::buildMap(std::vector<Planet>& planets) {
    planets.clear();
    planets.emplace_back("Earth", true);
    planets.emplace_back("Mars");
    planets.emplace_back("Venus");
    planets.emplace_back("Jupiter");
    planets.emplace_back("Saturn");
    planets.emplace_back("Neptune", true);

    planets[0].addRoute("Mars", 100, 10);
    planets[0].addRoute("Venus", 150, 15);
    planets[1].addRoute("Jupiter", 200, 20, 50);
    planets[2].addRoute("Saturn", 250, 25);
    planets[3].addRoute("Neptune", 300, 30);
}

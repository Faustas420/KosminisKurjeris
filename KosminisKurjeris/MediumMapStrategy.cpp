#include "MediumMapStrategy.h"

static void addBidirectionalRoute(std::vector<Planet>& planets,
    const std::string& a, const std::string& b,
    int fuel, int risk, int bonus = 0) {

    Planet* planetA = nullptr;
    Planet* planetB = nullptr;

    for (auto& p : planets) {
        if (p.getName() == a) planetA = &p;
        if (p.getName() == b) planetB = &p;
    }

    if (planetA) planetA->addRoute(b, fuel, risk, bonus);
    if (planetB) planetB->addRoute(a, fuel, risk, bonus);
}

void MediumMapStrategy::buildMap(std::vector<Planet>& planets) {
    planets = {
        Planet("Earth", true),
        Planet("Moon"),
        Planet("Mars"),
        Planet("Phobos"),
        Planet("Jupiter"),
        Planet("Europa"),
        Planet("Saturn"),
        Planet("Titan"),
        Planet("Pluto")
    };

    addBidirectionalRoute(planets, "Earth", "Moon", 30, 5);
    addBidirectionalRoute(planets, "Moon", "Mars", 80, 15);
    addBidirectionalRoute(planets, "Mars", "Phobos", 40, 20);
    addBidirectionalRoute(planets, "Phobos", "Jupiter", 120, 30);
    addBidirectionalRoute(planets, "Jupiter", "Europa", 70, 25);
    addBidirectionalRoute(planets, "Europa", "Saturn", 140, 35);
    addBidirectionalRoute(planets, "Saturn", "Titan", 90, 30);
    addBidirectionalRoute(planets, "Titan", "Pluto", 200, 50);
    addBidirectionalRoute(planets, "Moon", "Europa", 180, 40);
    addBidirectionalRoute(planets, "Jupiter", "Titan", 160, 35, 250);
}

std::string MediumMapStrategy::getGoalPlanet() const {
    return "Pluto";
}

std::string MediumMapStrategy::getStartPlanet() const {
    return "Earth";
}

std::string MediumMapStrategy::getMapDescription() const {
    return "Earth - Moon - Mars - Phobos - Jupiter - Europa - Saturn - Titan - Pluto (Goal)\n"
        "Extra routes: Moon–Europa, Jupiter–Titan (+250 fuel)";
}

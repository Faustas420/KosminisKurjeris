#include "HardMapStrategy.h"

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

void HardMapStrategy::buildMap(std::vector<Planet>& planets) {
    planets = {
        {"Sun", true}, {"Mercury"}, {"Venus", true}, {"Earth"}, {"Mars"},
        {"Centaurs"}, {"Uranus", true}, {"Neptune"}, {"Kuiper Belt"}
    };

    addBidirectionalRoute(planets, "Sun", "Mercury", 40, 15);
    addBidirectionalRoute(planets, "Mercury", "Venus", 60, 20);
    addBidirectionalRoute(planets, "Venus", "Earth", 80, 25);
    addBidirectionalRoute(planets, "Earth", "Mars", 100, 30);
    addBidirectionalRoute(planets, "Mars", "Centaurs", 160, 40);
    addBidirectionalRoute(planets, "Centaurs", "Uranus", 180, 45);
    addBidirectionalRoute(planets, "Uranus", "Neptune", 150, 50);
    addBidirectionalRoute(planets, "Neptune", "Kuiper Belt", 220, 60);
    addBidirectionalRoute(planets, "Earth", "Uranus", 320, 55);
    addBidirectionalRoute(planets, "Centaurs", "Kuiper Belt", 300, 70, 400);
}

std::string HardMapStrategy::getGoalPlanet() const {
    return "Kuiper Belt";
}

std::string HardMapStrategy::getStartPlanet() const {
    return "Sun";
}

std::string HardMapStrategy::getMapDescription() const {
    return "Sun - Mercury - Venus - Earth - Mars - Centaurs - Uranus - Neptune - Kuiper Belt (Goal)\n"
        "Extra routes: Earth–Uranus, Centaurs–Kuiper Belt (+400 fuel)";
}

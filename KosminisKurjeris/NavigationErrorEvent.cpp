#include "NavigationErrorEvent.h"
#include "Player.h"
#include <iostream>

NavigationErrorEvent::NavigationErrorEvent(const std::string& start)
    : startPlanet(start) {
}

void NavigationErrorEvent::apply(Player& player) {
    std::cout << "Navigation error! You are sent back to " << startPlanet << ".\n";
    player.moveTo(startPlanet);
}

std::string NavigationErrorEvent::getDescription() const {
    return "Navigation error!";
}

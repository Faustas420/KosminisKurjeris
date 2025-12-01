#include "StormEvent.h"
#include "Player.h"
#include <iostream>

void StormEvent::apply(Player& player) {
    std::cout << "A dangerous storm hit your ship! You lost fuel.\n";
    player.consumeFuel(10); 
}

std::string StormEvent::getDescription() const {
    return "Storm hits the ship!";
}

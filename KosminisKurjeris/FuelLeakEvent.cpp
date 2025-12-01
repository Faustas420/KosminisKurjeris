#include "FuelLeakEvent.h"
#include "Player.h"
#include <iostream>

void FuelLeakEvent::apply(Player& player) {
    std::cout << "Fuel leak detected! You lost 15 fuel.\n";
    player.consumeFuel(15); 
}

std::string FuelLeakEvent::getDescription() const {
    return "Fuel leak!";
}

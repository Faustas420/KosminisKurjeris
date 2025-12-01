#include "PiratesEvent.h"
#include "Player.h"
#include <iostream>

void PiratesEvent::apply(Player& player) {
    std::cout << "Pirates attacked! You lost some cargo.\n";
    player.loseCargo();
}

std::string PiratesEvent::getDescription() const {
    return "Pirates attack!";
}

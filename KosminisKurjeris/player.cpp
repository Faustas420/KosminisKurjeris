#include "Player.h"
#include <algorithm> 
#include <string>
#include "GameConstants.h" 

Player::Player(int initialFuel, std::string startPos)
    : fuel(initialFuel), cargoIntact(true), hasInsurance(false), currentPosition(startPos)
{
}

int Player::getFuel() const { return fuel; }
bool Player::hasCargo() const { return cargoIntact; }
bool Player::isInsured() const { return hasInsurance; }
const std::string& Player::getPosition() const { return currentPosition; }

void Player::consumeFuel(int amount) {
    fuel = std::max(0, fuel - amount);
}

void Player::addFuel(int amount) {
    fuel += amount;
}

void Player::loseCargo() {
    cargoIntact = false;
}

void Player::activateInsurance() {
    hasInsurance = true;
}

void Player::useInsurance() {
    hasInsurance = false;
}

void Player::moveTo(const std::string& destination) {
    currentPosition = destination;
}

bool Player::canAffordFuel(int cost) const {
    return fuel >= cost;
}

bool Player::canBuyInsurance() const {
    return fuel >= GameConstants::MIN_FUEL_FOR_INSURANCE && !hasInsurance;
}

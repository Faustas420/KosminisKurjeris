#pragma once
#include <string>

class Player {
private:
    int fuel;
    bool cargoIntact;
    bool hasInsurance;
    std::string currentPosition;

public:
    Player(int initialFuel, std::string startPos);

    int getFuel() const;
    bool hasCargo() const;
    bool isInsured() const;
    const std::string& getPosition() const;

    void consumeFuel(int amount);
    void addFuel(int amount);
    void loseCargo();
    void activateInsurance();
    void useInsurance();
    void moveTo(const std::string& destination);

    bool canAffordFuel(int cost) const;
    bool canBuyInsurance() const;
};
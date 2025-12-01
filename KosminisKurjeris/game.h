#pragma once
#include <vector>
#include <memory>
#include <string>

#include "Player.h"
#include "GameMap.h"
#include "IEvent.h"

class Game {
private:
    Player player;
    GameMap gameMap;
    std::vector<std::unique_ptr<IEvent>> eventList;
    int moveCount;

public:
    Game(int difficulty);
    void run();

private:
    int getInitialFuel(int difficulty) const;
    std::string getStartPosition(int difficulty) const;
    std::unique_ptr<IMapStrategy> createMapStrategy(int difficulty);

    void displayWelcome();
    void displayStatus();
    bool isGameActive() const;
    bool checkGameOver();
    bool checkVictory();

    void processPlayerTurn();
    void displayRoutes(const Planet& planet);
    void displayRoute(int index, const Route& route);
    int getPlayerChoice();
    bool isValidRouteChoice(int choice, const Planet& planet) const;
    void executeTravel(const Route& route);
    void handleFlightEvents(int riskPercent);
    void triggerRandomEvent();
    void handleArrival(int bonusFuel);
    void handleSpaceStation();
    void offerInsurance();
    void displayFarewell();
};

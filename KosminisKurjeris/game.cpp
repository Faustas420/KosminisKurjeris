#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "EventFactory.h"
#include "GameConstants.h"
#include "EasyMapStrategy.h"
#include "MediumMapStrategy.h"
#include "HardMapStrategy.h"

Game::Game(int difficulty)
    : player(getInitialFuel(difficulty), getStartPosition(difficulty)),
    gameMap(createMapStrategy(difficulty)),
    moveCount(0)
{
    srand((unsigned)time(nullptr));
    eventList = EventFactory::createEvents(gameMap.getStrategy()->getStartPlanet());
}

void Game::run() {
    displayWelcome();

    while (isGameActive()) {
      
        gameMap.displayMap();  

        displayStatus();

        if (checkGameOver() || checkVictory()) break;

        processPlayerTurn();
    }

    displayFarewell();
}



int Game::getInitialFuel(int difficulty) const {
    switch (difficulty) {
    case 1: return GameConstants::EASY_FUEL;
    case 2: return GameConstants::MEDIUM_FUEL;
    case 3: return GameConstants::HARD_FUEL;
    default: return GameConstants::EASY_FUEL;
    }
}

std::string Game::getStartPosition(int difficulty) const {
    return (difficulty == 3) ? "Sun" : "Earth";
}

std::unique_ptr<IMapStrategy> Game::createMapStrategy(int difficulty) {
    switch (difficulty) {
    case 1: return std::make_unique<EasyMapStrategy>();
    case 2: return std::make_unique<MediumMapStrategy>();
    case 3: return std::make_unique<HardMapStrategy>();
    default: return std::make_unique<EasyMapStrategy>();
    }
}


void Game::displayWelcome() {
    std::cout << "\n=== CARGO DELIVERY ===\n";
    std::cout << "Goal: Reach the final planet in as few moves as possible.\n";
    std::cout << "Controls: Enter route number.\n";
    std::cout << "0 = Map | 9 = Quit\n";
}

void Game::displayStatus() {
    std::cout << "\nSTATUS:\n";
    std::cout << "Planet: " << player.getPosition() << "\n";
    std::cout << "Fuel: " << player.getFuel()
        << " | Cargo: " << (player.hasCargo() ? "Yes" : "No")
        << " | Insurance: " << (player.isInsured() ? "Yes" : "No")
        << " | Moves: " << moveCount << "\n\n";
}


bool Game::isGameActive() const {
    return player.hasCargo() && player.getFuel() > 0;
}

bool Game::checkGameOver() {
    if (!player.hasCargo()) {
        std::cout << "\nCargo lost - Game Over!\n";
        return true;
    }
    if (player.getFuel() <= 0) {
        std::cout << "\nFuel depleted - Game Over!\n";
        return true;
    }
    return false;
}

bool Game::checkVictory() {
    if (player.getPosition() == gameMap.getStrategy()->getGoalPlanet()) {
        std::cout << "\nGoal reached in " << moveCount << " moves!\n";
        return true;
    }
    return false;
}


void Game::processPlayerTurn() {
    Planet* currentPlanet = gameMap.findPlanet(player.getPosition());
    if (!currentPlanet) return;

    currentPlanet->displayRoutes();

    int choice;
    std::cout << "Choose route: ";
    std::cin >> choice;

    if (choice == 0) return; 
    if (choice == 9) {      
        std::cout << "Exiting game.\n";
        player.loseCargo();
        return;
    }

    if (choice < 1 || choice >(int)currentPlanet->getRoutes().size()) {
        std::cout << "Invalid choice!\n";
        return;
    }

    const Route& selectedRoute = currentPlanet->getRoutes()[choice - 1];
    if (!player.canAffordFuel(selectedRoute.fuelCost)) {
        std::cout << "Not enough fuel!\n";
        return;
    }

    player.consumeFuel(selectedRoute.fuelCost);
    moveCount++;

    std::cout << "\nFlying to " << selectedRoute.destination
        << " (risk: " << selectedRoute.riskPercent << "%)\n";

    if (rand() % 100 < selectedRoute.riskPercent) {
        std::cout << "A dangerous event occurred!\n";
        triggerRandomEvent();
    }
    else {
        std::cout << "Flight successful.\n";
    }

    player.moveTo(selectedRoute.destination);

    Planet* arrivedPlanet = gameMap.findPlanet(player.getPosition());
    if (arrivedPlanet && arrivedPlanet->hasStation()) {
        std::cout << "\nYou landed at a space station. +"
            << GameConstants::STATION_REFUEL << " fuel.\n";
        player.addFuel(GameConstants::STATION_REFUEL);
    }

    if (selectedRoute.bonusFuel > 0) {
        std::cout << "Bonus fuel: +" << selectedRoute.bonusFuel << "\n";
        player.addFuel(selectedRoute.bonusFuel);
    }

    std::cout << std::endl;
}

void Game::displayFarewell() {
    std::cout << "\nGame over. Thanks for playing!\n";
}

void Game::triggerRandomEvent() {
    if (eventList.empty()) return;

    int idx = rand() % eventList.size();
    eventList[idx]->apply(player);
}

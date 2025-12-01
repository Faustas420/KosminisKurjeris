#pragma once
#include "IEvent.h"
#include <string>

class NavigationErrorEvent : public IEvent {
private:
    std::string startPlanet;

public:
    NavigationErrorEvent(const std::string& start);
    void apply(Player& player) override;
    std::string getDescription() const override;
};

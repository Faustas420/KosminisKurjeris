#pragma once
#include "IEvent.h"

class StormEvent : public IEvent {
public:
    void apply(Player& player) override;
    std::string getDescription() const override;
};

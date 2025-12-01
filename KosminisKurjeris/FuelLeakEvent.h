#pragma once
#include "IEvent.h"

class FuelLeakEvent : public IEvent {
public:
    void apply(Player& player) override;
    std::string getDescription() const override;
};

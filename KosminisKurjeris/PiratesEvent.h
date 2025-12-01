#pragma once
#include "IEvent.h"

class PiratesEvent : public IEvent {
public:
    void apply(Player& player) override;
    std::string getDescription() const override;
};

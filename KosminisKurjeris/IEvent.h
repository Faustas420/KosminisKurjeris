#pragma once
#include <string>
class Player; 

class IEvent {
public:
    virtual void apply(Player& player) = 0;

    virtual std::string getDescription() const = 0;

    virtual ~IEvent() = default;
};

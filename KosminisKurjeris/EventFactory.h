#pragma once
#include <vector>
#include <memory>
#include "IEvent.h"

class EventFactory {
public:
    static std::vector<std::unique_ptr<IEvent>> createEvents(const std::string& startPlanet);
};

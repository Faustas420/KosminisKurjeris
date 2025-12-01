#include "EventFactory.h"
#include "PiratesEvent.h"
#include "StormEvent.h"
#include "FuelLeakEvent.h"
#include "NavigationErrorEvent.h"
#include <memory>

std::vector<std::unique_ptr<IEvent>> EventFactory::createEvents(const std::string& startPlanet) {
    std::vector<std::unique_ptr<IEvent>> events;
    events.push_back(std::make_unique<PiratesEvent>());
    events.push_back(std::make_unique<StormEvent>());
    events.push_back(std::make_unique<FuelLeakEvent>());
    events.push_back(std::make_unique<NavigationErrorEvent>(startPlanet));
    return events;
}

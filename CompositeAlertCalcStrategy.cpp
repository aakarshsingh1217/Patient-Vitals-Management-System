#include "CompositeAlertCalcStrategy.h"

void CompositeAlertCalcStrategy::addStrategy(std::unique_ptr<AlertCalcStrategy> strategy) {
    strategies.push_back(std::move(strategy));
}

AlertLevel CompositeAlertCalcStrategy::calculateAlert(Patient& patient) {
    AlertLevel highestAlertLevel = AlertLevel::Green;

    for (const auto& strategy : strategies) {
        AlertLevel currentAlertLevel = strategy->calculateAlert(patient);
        if (currentAlertLevel > highestAlertLevel) {
            highestAlertLevel = currentAlertLevel;
        }
    }
    return highestAlertLevel;
}

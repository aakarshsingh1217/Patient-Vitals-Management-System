#ifndef COMPOSITE_ALERT_CALC_STRATEGY_H
#define COMPOSITE_ALERT_CALC_STRATEGY_H

#include "AlertCalcStrategy.h"
#include <vector>
#include <memory>

class CompositeAlertCalcStrategy : public AlertCalcStrategy {
public:
    void addStrategy(std::unique_ptr<AlertCalcStrategy> strategy);
    AlertLevel calculateAlert(Patient& patient) override;

private:
    std::vector<std::unique_ptr<AlertCalcStrategy>> strategies;
};

#endif // COMPOSITE_ALERT_CALC_STRATEGY_H

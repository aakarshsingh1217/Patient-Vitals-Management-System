// ERushStrategy.h
#ifndef ERUSH_STRATEGY_H
#define ERUSH_STRATEGY_H

#include "AlertCalcStrategy.h"

class ERushStrategy : public AlertCalcStrategy
{
public:
    AlertLevel calculateAlert(Patient& patient) override
    {
        int bodyTemperature = patient.getBodyTemperature();
        int brainActivity = patient.getBrainActivity();

        if (bodyTemperature > 38 && brainActivity > 110)
        {
            return AlertLevel::Red;
        }
        if (bodyTemperature > 38 && brainActivity > 100)
        {
            return AlertLevel::Yellow;
        }
        return AlertLevel::Green;
    }
};

#endif // ERUSH_STRATEGY_H
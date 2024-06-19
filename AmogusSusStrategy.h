#ifndef AMOGUS_SUS_STRATEGY_H
#define AMOGUS_SUS_STRATEGY_H

#include "AlertCalcStrategy.h"

class AmogusSusStrategy : public AlertCalcStrategy
{
public:
    AlertLevel calculateAlert(Patient& patient) override
    {
        int heartRate = patient.getHeartRate();

        if (heartRate > 220) return AlertLevel::Red;
        if (heartRate > 210) return AlertLevel::Orange;
        if (heartRate > 200) return AlertLevel::Yellow;
        return AlertLevel::Green;
    }
};

#endif // AMOGUS_SUS_STRATEGY_H
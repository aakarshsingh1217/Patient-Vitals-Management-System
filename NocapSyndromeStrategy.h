#ifndef NOCAP_SYNDROME_STRATEGY_H
#define NOCAP_SYNDROME_STRATEGY_H

#include "AlertCalcStrategy.h"

class NocapSyndromeStrategy : public AlertCalcStrategy
{
public:
    AlertLevel calculateAlert(Patient& patient) override
    {
        int oxygenSaturation = patient.getOxygenSaturation();

        if (oxygenSaturation < 90)
        {
            return AlertLevel::Red;
        }
        if (oxygenSaturation < 92)
        {
            return AlertLevel::Orange;
        }
        if (oxygenSaturation < 94)
        {
            return AlertLevel::Yellow;
        }
        return AlertLevel::Green;
    }
};

#endif

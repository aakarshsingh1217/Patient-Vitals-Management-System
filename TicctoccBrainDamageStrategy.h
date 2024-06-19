// TicctoccBrainDamageStrategy.h
#ifndef TICCTOCC_BRAIN_DAMAGE_STRATEGY_H
#define TICCTOCC_BRAIN_DAMAGE_STRATEGY_H

#include "AlertCalcStrategy.h"

class TicctoccBrainDamageStrategy : public AlertCalcStrategy
{
public:
    AlertLevel calculateAlert(Patient& patient) override
    {
        int age = patient.age();
        int brainActivity = patient.getBrainActivity();

        //std::cout << "Calculating Ticctocc Brain Damage Alert Level" << std::endl;
        //std::cout << "Age: " << age << ", Brain Activity: " << brainActivity << std::endl;


        //printf("%d", age);

        if (age < 35 && brainActivity < 10)
        {
            return AlertLevel::Red;
        }
        else if (age >= 35 && brainActivity < 20)
        {
            return AlertLevel::Red;
        }

        return AlertLevel::Green;
    }
};

#endif // TICCTOCC_BRAIN_DAMAGE_STRATEGY_H

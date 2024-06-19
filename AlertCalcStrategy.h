#ifndef ALERT_CALC_STRATEGY_H
#define ALERT_CALC_STRATEGY_H

#include "Patient.h"

#include "PatientAlertLevels.h"
class Patient;

class AlertCalcStrategy
{
public:
    virtual ~AlertCalcStrategy() = default;
    virtual AlertLevel calculateAlert(Patient& patient) = 0;
};

#endif
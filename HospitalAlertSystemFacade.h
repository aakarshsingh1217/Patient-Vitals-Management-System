#ifndef HOSPITAL_ALERT_SYSTEM_FACADE_H
#define HOSPITAL_ALERT_SYSTEM_FACADE_H

#include "AlertObserver.h"
#include "Patient.h"
#include <string>


class HospitalAlertSystemFacade : public AlertObserver
{
public:
    HospitalAlertSystemFacade();
    virtual ~HospitalAlertSystemFacade();

    void sendAlertForPatient(Patient* p);
    void updateAlertLevel(const std::string& patientID, const std::string& alertLevel) override;
};

#endif

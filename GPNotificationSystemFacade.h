#ifndef GP_NOTIFICATION_SYSTEM_FACADE_H
#define GP_NOTIFICATION_SYSTEM_FACADE_H

#include "AlertObserver.h"
#include "Patient.h"
#include <string>


class GPNotificationSystemFacade : public AlertObserver {
public:
    GPNotificationSystemFacade();
    virtual ~GPNotificationSystemFacade();

    void sendGPNotificationForPatient(Patient* p);
    void updateAlertLevel(const std::string& patientID, const std::string& alertLevel) override;
};

#endif

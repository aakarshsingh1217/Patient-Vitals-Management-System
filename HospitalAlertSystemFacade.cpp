#include "HospitalAlertSystemFacade.h"

#include <iostream>


HospitalAlertSystemFacade::HospitalAlertSystemFacade()
{ }

HospitalAlertSystemFacade::~HospitalAlertSystemFacade()
{ }

void HospitalAlertSystemFacade::sendAlertForPatient(Patient* p)
{
    if (p->alertLevel() == AlertLevel::Red) {
        // A mocked alert message. A real message would use an SMS/pager gateway or similar
        std::cout << std::endl;
        std::cout << "This is an alert to the hospital:" << std::endl;
        std::cout << "Patient: " << p->humanReadableID() << " has a critical alert level" << std::endl;
    }
}

void HospitalAlertSystemFacade::updateAlertLevel(const std::string& patientID, const std::string& alertLevel) {
    if (alertLevel == "Red") {
        //std::cout << "Hospital Alert: Patient " << patientID << " has reached a critical alert level: " << alertLevel << std::endl;
    }
}
#ifndef ALERTOBSERVER_H
#define ALERTOBSERVER_H

#include <string>

class AlertObserver {
public:
    virtual void updateAlertLevel(const std::string& patientID, const std::string& alertLevel) = 0;
    virtual ~AlertObserver() = default;
};

#endif
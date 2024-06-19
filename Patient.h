#ifndef PATIENT_H
#define PATIENT_H
#include "Person.h"
#include "AlertCalcStrategy.h"
#include "Vitals.h"
#include "AlertObserver.h"
#include <vector>
#include <memory>
#include <string>

#include "PatientAlertLevels.h"

class Vitals;
class AlertCalcStrategy;


namespace Diagnosis {
    extern const std::string AMOGUS_SUS;
    extern const std::string E_RUSH;
    extern const std::string NOCAP_SYNDROME;
    extern const std::string TICCTOCC_BRAIN_DAMAGE;
};

class Patient : public Person {
public:

    Patient(const std::string& firstName, const std::string& lastName, std::tm birthday);

    // return a calculated age for the patient
    // this calculation is not accurate, but is suitable for assignment purposes
    int age() const;

    // return a "unique" ID generated for the patient
    // this id is generated purely from patient details, and as such may have collisions
    std::string uid() const;
    
    // returns a "nice" ID for humans to interpret: lastname, firstname (UID)
    std::string humanReadableID() const;

    // patients have diagnoses of a disease
    // Note: the initial design consider multiple diagnoses added using addDiagnosis.
    // This was refactored to only consider the primary (i.e. the first) diagnosis.
    void addDiagnosis(const std::string& diagnosis);
    const std::string& primaryDiagnosis() const;

    const std::vector<std::string>& diagnoses() const;

    // add a vitals mesaurements record to the patient
    void addVitals(const Vitals* v, bool historical = false);
    const std::vector<const Vitals*> vitals() const;

    // patients have an alert level (green, yellow, orange, red) calculated from their disease and and their last vitals
    void setAlertLevel(AlertLevel level);
    const AlertLevel alertLevel() const { return _alertLevel; }

    void setAlertCalcStrategy(std::unique_ptr<AlertCalcStrategy> strategy);

    void updateAlertLevel();

    void addObserver(AlertObserver* observer);
    void removeObserver(AlertObserver* observer);
    void notifyObservers();

    int getHeartRate() const { return _latestVitals ? _latestVitals->HR() : 0; }
    int getBodyTemperature() const { return _latestVitals ? _latestVitals->BT() : 0; }
    int getBrainActivity() const { return _latestVitals ? _latestVitals->BA() : 0; }
    int getOxygenSaturation() const { return _latestVitals ? _latestVitals->SPO2() : 0; }


protected:
    std::vector<std::string> _diagnosis;
    std::vector<const Vitals*> _vitals;
    AlertLevel _alertLevel = AlertLevel::Green;
    std::unique_ptr<AlertCalcStrategy> alertCalcStrategy = nullptr;
    const Vitals* _latestVitals = nullptr;
    std::vector<AlertObserver*> observers;
    bool isHistorical;
    friend std::ostream& operator<<(std::ostream& os, const Patient& p);
};

#endif

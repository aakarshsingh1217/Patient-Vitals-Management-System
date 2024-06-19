#ifndef PATIENT_FILE_LOADER_H
#define PATIENT_FILE_LOADER_H

#include "AbstractPatientDatabaseLoader.h"
#include <string>
#include <vector>


// forward declare the patient class
class Patient;

class PatientFileLoader: public AbstractPatientDatabaseLoader
{
public:
    PatientFileLoader(const std::string& file);

    // loads a list of patients from a file and returns a vector of those patients
    std::vector<Patient*> loadPatientFile();

    void initialiseConnection() override {}
    void loadPatients(std::vector<Patient*>& patientIn) override;
    void closeConnection() override {}

private:
    std::string _file;
};

#endif

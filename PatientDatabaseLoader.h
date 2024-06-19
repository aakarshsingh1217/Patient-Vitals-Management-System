#ifndef PATIENT_DATABASE_LOADER_H
#define PATIENT_DATABASE_LOADER_H

#include "AbstractPatientDatabaseLoader.h"


// This is a simulated class. It does not really connect to the database
class PatientDatabaseLoader : public AbstractPatientDatabaseLoader {
public:

    // Inherited via AbstractPatientDatabaseLoader
    virtual void initialiseConnection() override;

    virtual void loadPatients(std::vector<Patient*>& patientIn) override;

    virtual void closeConnection() override;

};

#endif

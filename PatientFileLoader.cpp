#include "PatientFileLoader.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "Patient.h"
#include "Vitals.h"

PatientFileLoader::PatientFileLoader(const std::string& file) :
    _file(file)
{
}

std::vector<Patient*> PatientFileLoader::loadPatientFile()
{
    std::vector<Patient*> patients;

    std::ifstream inFile(_file);
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            std::stringstream ss(line);
            std::string id, dob, name, diseases, vitals;

            std::getline(ss, id, '/');
            std::getline(ss, dob, '/');
            std::getline(ss, name, '/');
            std::getline(ss, diseases, '/');
            std::getline(ss, vitals);

            // Parse the name
            std::string firstName = name.substr(name.find(",") + 1);
            std::string lastName = name.substr(0, name.find(","));

            // Parse the date of birth
            std::tm birthday = {};
            std::istringstream dobStream(dob);
            dobStream >> std::get_time(&birthday, "%d-%m-%Y");

            // Create a new Patient object
            Patient* patient = new Patient(firstName, lastName, birthday);

            // Parse and add diagnoses
            std::stringstream diseasesStream(diseases);
            std::string diagnosis;
            while (std::getline(diseasesStream, diagnosis, ',')) {
                patient->addDiagnosis(diagnosis);
            }

            // Parse and add vitals
            std::stringstream vitalsStream(vitals);
            std::string vital;
            while (std::getline(vitalsStream, vital, ';')) {
                std::stringstream vitalStream(vital);
                int heartRate, oxygenSaturation, bodyTemperature, brainActivity;
                char comma; // to consume the commas
                vitalStream >> heartRate >> comma >> oxygenSaturation >> comma >> bodyTemperature >> comma >> brainActivity;
                Vitals* v = new Vitals(heartRate, oxygenSaturation, bodyTemperature, brainActivity);
                patient->addVitals(v, true);
            }

            patients.push_back(patient);
        }
    } else {
        std::cerr << "Failed to open file: " << _file << std::endl;
    }

    return patients;
}

void PatientFileLoader::loadPatients(std::vector<Patient*>& patientIn) {
    patientIn = loadPatientFile();
}
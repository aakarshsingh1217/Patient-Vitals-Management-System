#include "Patient.h"

#include "Vitals.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include "CompositeAlertCalcStrategy.h"
#include "AmogusSusStrategy.h"
#include "ERushStrategy.h"
#include "NocapSyndromeStrategy.h"
#include "TicctoccBrainDamageStrategy.h"


using namespace std;

const std::string Diagnosis::AMOGUS_SUS = "AmogusSus";
const std::string Diagnosis::E_RUSH = "ERush";
const std::string Diagnosis::NOCAP_SYNDROME = "NocapSyndrome";
const std::string Diagnosis::TICCTOCC_BRAIN_DAMAGE = "TicctoccBrainDamage";



Patient::Patient(const std::string& firstName, const std::string& lastName, std::tm birthday) :
    Person(firstName, lastName, birthday),
    alertCalcStrategy(nullptr),
    isHistorical(true)
{
}

int Patient::age() const
{	
    // corrected age function to calculate age from current time, learnt from learncpp.com
    // Get the current time
    time_t now = time(nullptr);
    tm* currentTime = localtime(&now);

    // Calculate age
    int age = currentTime->tm_year + 1900 - (_birthday.tm_year + 1900);
    if ((_birthday.tm_mon > currentTime->tm_mon) ||
        (_birthday.tm_mon == currentTime->tm_mon && _birthday.tm_mday > currentTime->tm_mday)) {
        // Subtract one year if the birthday hasn't occurred yet this year
        age--;
    }
    return age;
}

std::string Patient::uid() const
{
    std::stringstream ss;
    ss << static_cast<char>(std::tolower(_lastName.at(0)))
       << static_cast<char>(std::tolower(_firstName.at(0)))
       << std::setfill('0') << std::setw(2) << (_birthday.tm_mon + 1) 
       << _birthday.tm_year;
    return ss.str();
}

std::string Patient::humanReadableID() const
{

    return "" + _lastName + ", " + _firstName + " (" + uid() + ")";
}

std::ostream& operator<<(std::ostream& os, const Patient& p)
{
    os << p.uid() << "/" << std::put_time(&p._birthday, "%d-%m-%Y") << "/" << p._lastName << "," << p._firstName << "/";
    
    auto diagnoses = p.diagnoses();
    for (auto itr = diagnoses.begin(); itr != diagnoses.end(); ++itr) {
        if (itr != diagnoses.begin()) os << ";";
        os << *itr;
    }

    os << "/";

    auto vitals = p.vitals();
    for (auto itr = vitals.begin(); itr != vitals.end(); ++itr) {
        if (itr != vitals.begin()) os << ";";
        os << **itr;
    }

    return os;
}

void Patient::addDiagnosis(const std::string& diagnosis)
{
    _ASSERT(diagnosis == Diagnosis::AMOGUS_SUS ||
        diagnosis == Diagnosis::E_RUSH ||
        diagnosis == Diagnosis::NOCAP_SYNDROME ||
        diagnosis == Diagnosis::TICCTOCC_BRAIN_DAMAGE);
    _diagnosis.push_back(diagnosis);

    auto compositeStrategy = std::make_unique<CompositeAlertCalcStrategy>();
    for (const auto& diag : _diagnosis) {
        if (diag == Diagnosis::AMOGUS_SUS) {
            compositeStrategy->addStrategy(std::make_unique<AmogusSusStrategy>());
        }
        else if (diag == Diagnosis::E_RUSH) {
            compositeStrategy->addStrategy(std::make_unique<ERushStrategy>());
        }
        else if (diag == Diagnosis::NOCAP_SYNDROME) {
            compositeStrategy->addStrategy(std::make_unique<NocapSyndromeStrategy>());
        }
        else if (diag == Diagnosis::TICCTOCC_BRAIN_DAMAGE) {
            compositeStrategy->addStrategy(std::make_unique<TicctoccBrainDamageStrategy>());
        }
    }
    setAlertCalcStrategy(std::move(compositeStrategy));
}

const std::string& Patient::primaryDiagnosis() const
{
    if (!_diagnosis.empty()) {
        return _diagnosis[0];
    }
    static const std::string emptyString;
    return emptyString;
}

const std::vector<std::string>& Patient::diagnoses() const
{
    return _diagnosis;
}

void Patient::addVitals(const Vitals* v, bool historical)
{
    _vitals.push_back(v);
    _latestVitals = v;
    isHistorical = historical;
    
    if (!isHistorical) {
        updateAlertLevel();
    }
}

const std::vector<const Vitals*> Patient::vitals() const
{
    return _vitals;
}

void Patient::setAlertLevel(AlertLevel level)
{
    _alertLevel = level;

    if (_alertLevel > AlertLevel::Green) {
        cout << "Patient: " << humanReadableID() << " has an alert level: ";
        switch (_alertLevel) {
        case AlertLevel::Yellow:
            cout << "Yellow";
            break;
        case AlertLevel::Orange:
            cout << "Orange";
            break;
        case AlertLevel::Red:
            cout << "Red";
            break;
        }
        cout << endl;
    }
    notifyObservers();
}

void Patient::setAlertCalcStrategy(std::unique_ptr<AlertCalcStrategy> strategy) {
    alertCalcStrategy = std::move(strategy);
}

void Patient::updateAlertLevel() {
    if (alertCalcStrategy) {
        setAlertLevel(alertCalcStrategy->calculateAlert(*this));
    }
}

void Patient::addObserver(AlertObserver* observer) {
    observers.push_back(observer);
}

void Patient::removeObserver(AlertObserver* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Patient::notifyObservers() {
    for (AlertObserver* observer : observers) {
        observer->updateAlertLevel(uid(), "Red");
    }
}

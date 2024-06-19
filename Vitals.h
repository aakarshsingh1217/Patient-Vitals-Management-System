#ifndef VITALS_H
#define VITALS_H

#include <iostream>


class Vitals
{
public:
    Vitals(int hr, int spo2, int bt, int ba) :
        _heartRate(hr),
        _oxygenSaturation(spo2),
        _bodyTemperature(bt),
        _brainActivity(ba)
    { }

    int HR() const { return _heartRate; }
    int SPO2() const { return _oxygenSaturation; }
    int BT() const { return _bodyTemperature; }
    int BA() const { return _brainActivity; }

    friend std::ostream& operator<<(std::ostream& os, const Vitals& p);

protected:
    int _heartRate;
    int _oxygenSaturation;
    int _bodyTemperature;
    int _brainActivity;
};

#endif

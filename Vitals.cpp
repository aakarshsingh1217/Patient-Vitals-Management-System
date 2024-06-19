#include "Vitals.h"

#include <iostream>


std::ostream& operator<<(std::ostream& os, const Vitals& p)
{
    os << p.HR() << "," << p.SPO2() << "," << p.BT() << "," << p.BA();
    return os;
}

# CMakeList.txt : CMake project for A2, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("A2")

# Add source to this project's executable.
add_executable (A2
    "AbstractPatientDatabaseLoader.h"
    "GPNotificationSystemFacade.cpp" "GPNotificationSystemFacade.h"
    "HospitalAlertSystemFacade.cpp" "HospitalAlertSystemFacade.cpp"
    "main.cpp"
    "Patient.cpp" "Patient.h"
    "PatientAlertLevels.h"
    "PatientDatabaseLoader.cpp" "PatientDatabaseLoader.h"
    "PatientFileLoader.cpp" "PatientFileLoader.h"
    "PatientManagementSystem.cpp" "PatientManagementSystem.h"
    "Person.cpp" "Person.h"
    "Vitals.cpp" "Vitals.h"
 "AlertCalcStrategy.h" "AmogusSusStrategy.h" "ERushStrategy.h" "NocapSyndromeStrategy.h" "TicctoccBrainDamageStrategy.h" "CompositeAlertCalcStrategy.h" "CompositeAlertCalcStrategy.cpp" "AlertObserver.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET A2 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

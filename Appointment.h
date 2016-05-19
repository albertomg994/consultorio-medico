//
//  Appointment.h
//  T10-Juez-I
//
//  Created by Alberto Miedes on 13/5/16.
//  Copyright © 2016 Alberto Miedes. All rights reserved.
//

#ifndef Appointment_h
#define Appointment_h

#include <string>

#include "Date.h"

using namespace std;

using Patient = std::string;   // Patient type

/**
 * Appointment class. An appointment is a patient-date association.
 */
class Appointment {
private:

    Patient _patient;
    Date _date;

public:

    // Constructor - create new appointment
    Appointment(Patient p, Date d) : _patient(p), _date(d) {}

    // Getters
    const Patient & patient() const { return _patient; }
    const Date & date() const { return _date; }

    // Others
    string to_string() {
        return "Patient: " + _patient + " - Date: " + _date.to_string();
    }
};

#endif /* Appointment_h */

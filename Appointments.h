//
//  Appointments.h
//  T10-Juez-I
//
//  Created by Alberto Miedes on 14/5/16.
//  Copyright © 2016 Alberto Miedes. All rights reserved.
//

#ifndef Appointments_h
#define Appointments_h

#include <list>
#include "Appointment.h"

using namespace std;

/**
 * Thrown when trying to make an appointment in an already taken date
 */
class DateAlreadyTakenException : public ClinicException {
public:
    DateAlreadyTakenException() : ClinicException("Fecha ocupada") {};
};

/**
 * Thrown when trying to get an appointment from an empty appointment list
 */
class EmptyAppointmentListException : public ClinicException {
public:
    EmptyAppointmentListException() : ClinicException("No hay pacientes") {};
};


/**
 * Appointments class. Represents the series of appointments for a Medic
 */
class Appointments {
private:

    list<Appointment> _appointments;

public:

    // Getters - O(1)
    const list<Appointment> & appointments() const { return _appointments; }
    size_t size() const { return _appointments.size(); }

    /**
     * Returns a list with all appointments on a concrete day
     * Complexity: O(n), n = _appointments.size()
     *
     * @param d The date
     * @return The list
     */
    list<Appointment> get_appointments_on_date(const Date &d) const {

        list<Appointment> ret;

        list<Appointment>::const_iterator it = _appointments.cbegin();
        while (it != _appointments.cend()) {
            // We only have to check same day
            if ((*it).date().day() == d.day()) ret.push_back(*it);
            it++;
        }

        return ret;
    }

    /**
     * Pushes a new appointment to appointments list. If the new appointment
     * collides with another one's date, throw exception.
     * Complexity: O(n), n = _appointments.size()
     *
     * @param a Appointment to insert in appointments list.
     * @throws DateAlreadyTakenException if trying to make and appointment on
     * an already taken date.
     */
    void new_appointment(const Appointment & a) {

        list<Appointment>::iterator it = _appointments.begin();

        // Search insert position
        while (a.date() > (*it).date() && it != _appointments.end()) it++;   // O(n)

        // Check if date is already taken
        if (a.date() == (*it).date()) throw DateAlreadyTakenException();

        _appointments.insert(it, a);    // O(1)
    }

    /**
     * Returns a const referente to next appointment in list
     * Complexity: O(1)
     *
     * @return const referente to next appointment in list
     * @throws EmptyAppointmentListException if list is empty.
     */
    const Appointment & next_appointment() const {

        if (_appointments.empty())
            throw EmptyAppointmentListException();

        return _appointments.front();
    }

    /**
     * Deletes first appointment from list
     * Complexity: O(1)
     *
     * @throws EmptyAppointmentListException if list is empty.
     */
    void pop_appointment() {

        if (_appointments.empty())
            throw EmptyAppointmentListException();

        _appointments.pop_front();
    }

};

#endif /* Appointments_h */

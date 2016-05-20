//
//  Consultorio.h
//  T10-Juez-I
//
//  Created by Alberto Miedes on 13/5/16.
//  Copyright © 2016 Alberto Miedes. All rights reserved.
//

#ifndef Clinic_h
#define Clinic_h

#include <string>
#include <list>
#include <iosfwd>
#include "TreeMap.h"
#include "Appointment.h"
#include "Appointments.h"
#include "Date.h"
#include "ClinicException.h"

using namespace std;

using Medic = std::string;     // Medic type
using Patient = std::string;   // Patient type

struct PatientDate {
    string paciente;
    unsigned int hora;
    unsigned int minuto;
};

string format_patient_date(struct PatientDate pd) {

    string s = pd.paciente + " ";

    if (pd.hora < 10) { s += "0" + to_string(pd.hora); }
    else s += to_string(pd.hora);

    s += ":";

    if (pd.minuto < 10) { s += "0" + to_string(pd.minuto); }
    else s += to_string(pd.minuto);

    return s;
}

/**
 * Main class. Keeps track of all the medics in the system and their appointments.
 */
class Clinic {
private:

    TreeMap<Medic, Appointments> _medics;

public:

    /**
     * nuevoMedico(m) - creates a new medic in the clinic. If it was already
     * in the system, it is not modified.
     * Complexity: O(logN), N = _medics.size()
     *
     * @param m The name of new medic
     */
    void nuevoMedico(Medic m) {
        _medics[m];    // Si no existe lo crea, pero si existe no modifica el valor.
    }

    /**
     * Patient p makes an appintment with m Medic on Date d.
     * A patient may have several appointments with the same medic as long as
     * they're not in the same moment (hour:minute)
     * Complexity: max( O(logN), O(m) ), N = _medics.size(), m = _appointments.size()
     *
     * @param p The patient who wants an appointment
     * @param m The medic the patient wants to visit
     * @param d The date of the appointment
     * @throws MedicNotFoundException si el médico no está dado de alta.
     * @throws EFechaOcupada si la fecha ya está reservada.
     */
    void pideConsulta(Patient p, Medic m, Date d) {

        // Get an iterator pointing at the medic
        TreeMap<Medic, Appointments>::Iterator it = _medics.find(m);    // O(logN) ----> Revisar si no viene mejor operator[]

        // If medic doesn't exist, throw exception
        if (it == _medics.end()) throw MedicNotFoundException();        // O(1)

        // Get medic's appointment list
        Appointments* apps = &(it.value());                             // O(1)

        // Create new appointment
        Appointment a(p, d);

        // Add the new appointment
        apps->new_appointment(a);   // O(m), m = _appointments.size()
    }

    /**
     * Retrieves next patient to be 'treated' by a medic. For 'next patient' we
     * understand the one who has the closest date.
     * Complexity: O(logN), N = _medics.size()
     *
     * @param m Medic whose next patient we want to retrieve
     * @throws MedicNotFoundException if medic is not present in the clinic.
     * @throws EmptyAppointmentListException if medic has no patients assigned.
     */
    const Patient & siguientePaciente(Medic m) const {

        // Get an iterator pointing at the medic
        TreeMap<Medic, Appointments>::ConstIterator it = _medics.find(m);   // O(logN)

        // If medic doesn't exist, throw exception
        if (it == _medics.cend()) throw MedicNotFoundException();           // O(1)

        // En este caso he optado por realizar toda la operación en una misma línea
        // pues al tratarse de un observador, sólo me deja utilizar ConstIterator
        return it.value().next_appointment().patient();                     // O(1)
    }

    /**
     * Deletes m's next patient. For 'next patient' we understand the one who
     * has the closest date.
     * Complexity: O(logN), N = _medics.size()
     *
     * @throws MedicNotFoundException if medic is not present in the clinic.
     * @throws EmptyAppointmentListException if medic has no patients assigned.
     */
    void atiendeConsulta(Medic m) {

        // Obtener un iterador apuntando al médico m
        TreeMap<Medic, Appointments>::Iterator it = _medics.find(m);    // O(logN)

        // Si el médico no existe, lanzar una excepción
        if (it == _medics.end()) throw MedicNotFoundException();        // O(1)

        // Obtener una referencia modificable a las citas del médico
        Appointments* aps = &(it.value());                              // O(1)

        // Get next appointment (throws EmptyAppointmentListException)
        aps->pop_appointment();                                         // O(1)
    }

    /**
     * listaPacientes(m,f) - devuele la lista de pacientes de un cierto médico
     * (m) que tienen cita el día (f). Se supone que el día es un número entero
     * correcto. Si el médico no tiene pacientes ese día,
     * la lista de retorno será vacía.
     * Complexity: max( O(logN), O(m) ), N = _medics.size(), m = appointments.size()
     *
     * @throws MedicNotFoundException if medic is not present in the clinic.
     */
    list<struct PatientDate> listaPacientes(Medic m, Date d) const {

        // Obtener un iterador apuntando al médico m
        TreeMap<Medic, Appointments>::ConstIterator it = _medics.find(m);   // O(logN)

        // Si el médico no existe, lanzar una excepción
        if (it == _medics.cend()) throw MedicNotFoundException();           // O(1)

        // Obtener una referencia constante a las citas del médico
        Appointments aps = it.value();                                      // O(1)

        // Obtener la lista de citas en la fecha indicada
        list<Appointment> aps_date = aps.get_appointments_on_date(d);       // O(m), m = appointments.size()

        list<PatientDate> patients;

        list<Appointment>::const_iterator apps_it = aps_date.cbegin();
        while (apps_it != aps_date.cend()) {    // Body -> O(1) - Loop: O(q), q = aps_date.size()

            struct PatientDate aux;

            aux.paciente = (*apps_it).patient();
            aux.hora = (*apps_it).date().hour();
            aux.minuto = (*apps_it).date().minute();

            patients.push_back(aux);

            apps_it++;
        }

        return patients;
    }

    /**
     * Returns m's number of appointments.
     * Complexity: O(logN), N = _medics.size()
     *
     * @throws MedicNotFoundException if medic is not present in the clinic.
     */
    size_t numero_citas(Medic m) const {

        // Obtener un iterador apuntando al médico m
        TreeMap<Medic, Appointments>::ConstIterator it = _medics.find(m);   // O(logN)

        // Si el médico no existe, lanzar una excepción
        if (it == _medics.cend()) throw MedicNotFoundException();           // O(1)

        // Obtener una referencia constante a las citas del médico
        Appointments aps = it.value();                                      // O(1)

        return aps.size();
    }

};

#endif /* Consultorio_h */

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

class Clinic {
private:
    
    TreeMap<Medic,Appointments> _medics;

public:

    /**
     * nuevoMedico(m) - da de alta un nuevo médico en el consultorio
     * Si el médico ya estaba en el consultorio éste no se modifica.
     */
    void nuevoMedico(Medic m) {
        _medics[m];    // Si no existe lo crea, pero si existe no modifica el valor.
    }

    /**
     * pideConsulta(p,m,f) - un paciente (p) pide consulta con un médico (m)
     * para una fecha (f).
     * Un paciente puede tener varias citas con el mismo médico, siempre que
     * sean en distinto momento.
     *
     * @throws MedicNotFoundException si el médico no está dado de alta.
     * @throws EFechaOcupada si la fecha ya está reservada.
     */
    void pideConsulta(Patient p, Medic m, Date d) {
        
        // Obtener un iterador apuntando al médico m
        TreeMap<Medic, Appointments>::Iterator it = _medics.find(m);    // O(logN)
        
        // Si el médico no existe, lanzar una excepción
        if (it == _medics.end()) throw MedicNotFoundException();        // O(1)

        // Obtener una referencia modificable a las citas del médico
        Appointments aps = it.value();                                  // O(1)

        // Create new appointment and try to add it to the medic's list
        Appointment a(p, d);
        
        //cout << "Size of appointments was " << aps.size() << endl;
        it.value().new_appointment(a); // --> esta funciona
        //aps.new_appointment(a); // --> esta no, solo modifica la copia
        //aps.new_appointment(a);   ----> ESTO ERA UN BUG, NO INSERTABA    // O(n), n = appointments.size()
        //cout << "Size of appointments is now " << aps.size() << endl;
    }

    /**
     * siguientePaciente(m) - consulta el paciente al que le toca el turno de
     * ser atendido por un médico (m). Suponemos que el siguiente paciente es el
     * que tiene la fecha menor.
     *
     * @throws MedicNotFoundException if medic is not present in the clinic.
     * @throws EmptyAppointmentListException if medic has no patients assigned.
     */
    const Patient & siguientePaciente(Medic m) const {
        
        // Obtener un iterador apuntando al médico m
        TreeMap<Medic, Appointments>::ConstIterator it = _medics.find(m);   // O(logN)
        
        // Si el médico no existe, lanzar una excepción
        if (it == _medics.cend()) throw MedicNotFoundException();           // O(1)
        
        // Obtener una referencia modificable a las citas del médico
        Appointments aps = it.value();                                      // O(1)
        
        // Get next appointment (throws EmptyAppointmentListException)
        Appointment ap = aps.next_appointment();
        
        // Return patient
        //return ap.patient();      // (!!!!!!!!), es lo mismo que antes, no se modificaba la original
        return it.value().next_appointment().patient(); // ----> DEBUGGING
    }
    
    /**
     * atiendeConsulta(m) - elimina el siguiene paciente de un médico (m).
     * Suponemos que el siguiente paciente es el que tiene una fecha menor.
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
        Appointments aps = it.value();                                  // O(1)
        
        // Get next appointment (throws EmptyAppointmentListException)
        aps.pop_appointment();                                          // O(1)
        
        // (!!!!!) ---> DEBUGGING, POR LO MISMO DE SIEMPRE
        it.value().pop_appointment();
    }

    /**
     * listaPacientes(m,f) - devuele la lista de pacientes de un cierto médico
     * (m) que tienen cita el día (f). Se supone que el día es un número entero
     * correcto. Si el médico no tiene pacientes ese día,
     * la lista de retorno será vacía.
     *
     * @throws MedicNotFoundException if medic is not present in the clinic.
     */
    list<Patient> listaPacientes(Medic m, Date d) const {
        
        // Obtener un iterador apuntando al médico m
        TreeMap<Medic, Appointments>::ConstIterator it = _medics.find(m);   // O(logN)
        
        // Si el médico no existe, lanzar una excepción
        if (it == _medics.cend()) throw MedicNotFoundException();           // O(1)
        
        // Obtener una referencia constante a las citas del médico
        Appointments aps = it.value();                                      // O(1)
        
        // Obtener la lista de citas en la fecha indicada
        list<Appointment> aps_date = aps.get_appointments_on_date(d);       // O(n), n = appointments.size()
        
        // Quedarnos con los pacientes únicos
        list<Patient> pats;
        bool unique = true;
        
        list<Appointment>::const_iterator aps_it = aps_date.cbegin();
        while (aps_it != aps_date.cend()) {
            
            // For each appointment, check if patient is unique in "pats"
            list<Patient>::const_iterator pats_it = pats.cbegin();
            while (unique && pats_it != pats.cend()) {
                if ((*aps_it).patient() == *pats_it) unique = false;
                pats_it++;
            }
            
            if (unique) pats.push_back((*aps_it).patient());
            aps_it++;
            unique = true;
        }

        return pats;
    }
    
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

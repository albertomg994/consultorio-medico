//
//  ClinicIO.h
//  T10-Juez-I
//
//  Created by Alberto Miedes on 20/5/16.
//  Copyright © 2016 Alberto Miedes. All rights reserved.
//

#ifndef ClinicIO_h
#define ClinicIO_h

#include <string>
#include <iostream>
#include "Clinic.h"

using namespace std;

using Medic = string;     // Medic type
using Patient = string;   // Patient type

/**
 * Auxiliary class with static methods whose objective is to match the
 * way input cases are provided to methods operating over the Clinic TAD
 */
class ClinicIO {
public:
    
    static void nuevoMedico(Clinic &c) {
        
        string medico;
        
        // Read operation input
        cin >> medico;
        
        // Run operation
        c.nuevoMedico(medico);
    }
    
    static void pideConsulta(Clinic &c) {
        
        string paciente, medico;
        unsigned int dia, hora, minuto;
        
        // Read operation input
        cin >> paciente;
        cin >> medico;
        cin >> dia >> hora >> minuto;
        
        Date d(dia, hora, minuto);
        
        // Run operation
        try {
            c.pideConsulta(paciente, medico, d);
        } catch (MedicNotFoundException mnfe) {
            cout << mnfe.msg() << endl;
            cout << "---" << endl;
        } catch (DateAlreadyTakenException date) {
            cout << date.msg() << endl;
            cout << "---" << endl;
        }
    }
    
    static void atiendeConsulta(Clinic &c) {
        
        string medico;
        
        // Read operation input
        cin >> medico;
        
        // Run operation
        try {
            c.atiendeConsulta(medico);
        } catch (MedicNotFoundException mnfe) {
            cout << mnfe.msg() << endl;
            cout << "---" << endl;
        } catch (EmptyAppointmentListException eale) {
            cout << eale.msg() << endl;
            cout << "---" << endl;
        }
    }
    
    static void listaPacientes(Clinic &c) {
        
        string medico;
        unsigned int dia;
        
        // Read operation input
        cin >> medico;
        cin >> dia;
        
        Date d_lista(dia, 0, 0);
        
        // Run operation
        try {
            
            // retrieve patient list
            list<struct PatientDate> l = c.listaPacientes(medico, d_lista);
            cout << "Doctor " << medico << " dia " << d_lista.day() << endl;
            
            // print list
            list<struct PatientDate>::const_iterator it = l.cbegin();
            if (l.size() == 0) cout << endl;
            while (it != l.cend()) {
                cout << format_patient_date(*it) << endl;
                it++;
            }
        } catch (MedicNotFoundException mnfe) {
            cout << mnfe.msg() << endl;
        }
        cout << "---" << endl;
    }
    
    static void siguientePaciente(Clinic &c) {
        
        string medico;
        
        // Read operation input
        cin >> medico;
        
        // Run operation
        cout << "Siguiente Paciente doctor " << medico << endl;
        try {
            string sig_pac = c.siguientePaciente(medico);
            cout << sig_pac << endl;
        } catch (MedicNotFoundException mnfe) {
            cout << mnfe.msg() << endl;
        } catch (EmptyAppointmentListException eale) {
            cout << eale.msg() << endl;
        }
        cout << "---" << endl;
        
    }
    
    static void operacionNoValida() {
        // ...
    }

};

#endif /* ClinicIO_h */
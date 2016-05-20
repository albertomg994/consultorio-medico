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

class ClinicIO {
public:
    
    // No genera salida
    static void nuevoMedico(Clinic &c) {
        
        string medico;
        
        cin >> medico;
        
        //cout << "nuevoMedico(" << medico << ")" << endl;
        
        c.nuevoMedico(medico);
    }
    
    // No genera salida
    static void pideConsulta(Clinic &c) {
        
        string paciente, medico;
        unsigned int dia, hora, minuto;
        
        cin >> paciente;
        cin >> medico;
        cin >> dia >> hora >> minuto;
        
        
        
        //cout << "pideConsulta(" << paciente << ", " << medico << ", " << "fecha" << ")" << endl;
        
        //cout << "d: " << dia << " h: " << hora << " m: " << minuto << endl;
        Date d(dia, hora, minuto);
        
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
    
    // No genera salida
    static void atiendeConsulta(Clinic &c) {
        
        string medico;
        
        cin >> medico;
        
        //cout << "atiendeConsulta(" << medico << ")" << endl;
        
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
    
    // SI genera salida
    static void listaPacientes(Clinic &c) {
        
        string medico;
        unsigned int dia;
        
        cin >> medico;
        cin >> dia;
        
        //cout << "d: " << dia << " h: " << 0 << " m: " << 0 << endl;
        Date d_lista(dia, 0, 0);
        
        //cout << "listaPacientes(" << medico << ", " << "fecha" << ")" << endl;
        
        try {
            list<struct PatientDate> l = c.listaPacientes(medico, d_lista);
            cout << "Doctor " << medico << " dia " << d_lista.day() << endl;
            list<struct PatientDate>::const_iterator it = l.cbegin();
            if (l.size() == 0) cout << endl;
            while (it != l.cend()) {
                cout << format_patient_date(*it) << endl;
                it++;
            }
            cout << "---" << endl;
        } catch (MedicNotFoundException mnfe) {
            cout << mnfe.msg() << endl;
            cout << "---" << endl;
        }
    }
    
    // SI genera salida
    static void siguientePaciente(Clinic &c) {
        
        string medico;
        
        cin >> medico;
        
        //cout << "siguientePaciente(" << medico << ")" << endl;
        
        cout << "Siguiente Paciente doctor " << medico << endl;
        
        try {
            string sig_pac = c.siguientePaciente(medico);
            //cout << "Siguiente Paciente doctor " << medico << endl;
            cout << sig_pac << endl;
            cout << "---" << endl;
        } catch (MedicNotFoundException mnfe) {
            cout << mnfe.msg() << endl;
            cout << "---" << endl;
        } catch (EmptyAppointmentListException eale) {
            cout << eale.msg() << endl;
            cout << "---" << endl;
        }
        
    }
    
    // No genera salida
    static void operacionNoValida() {
        //cout << "Operación no válida" << endl;
    }

};

#endif /* ClinicIO_h */
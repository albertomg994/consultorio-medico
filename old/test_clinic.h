//
//  test_clinic.h
//  T10-Juez-I
//
//  Created by Alberto Miedes on 19/5/16.
//  Copyright © 2016 Alberto Miedes. All rights reserved.
//

#ifndef test_clinic_h
#define test_clinic_h

#include "Clinic.h"

using namespace std;

using Medic = std::string;     // Medic type
using Patient = std::string;   // Patient type

void test_new_medic();
void test_new_appointment();
void test_next_patient();
void test_treat_patient();
void test_list_patients();

void test_clinic() {
    
    test_new_medic();
    test_new_appointment();
    test_list_patients();
    test_next_patient();
}

void test_new_medic() {
    
    Clinic c;
    
    c.nuevoMedico("Medico 1");
    c.nuevoMedico("Medico 2");
}

void test_new_appointment() {
    
    Clinic c;
    
    c.nuevoMedico("Medico 1");
    c.nuevoMedico("Medico 2");
    
    // Insertar una cita correctamente
    c.pideConsulta("Paciente 1", "Medico 1", Date(1, 1, 1));
    c.pideConsulta("Paciente 1", "Medico 1", Date(2, 1, 1));
    c.pideConsulta("Paciente 2", "Medico 1", Date(3, 1, 1));
    c.pideConsulta("Paciente 3", "Medico 1", Date(4, 1, 1));
    
    cout << "Was:" << c.numero_citas("Medico 1") << endl;
    assert(c.numero_citas("Medico 1") == 4);
    
    // Intentar insertar una cita para un médico no existente
    try {
        c.pideConsulta("Paciente 1", "Medico invisible", Date(23, 12, 05));
    } catch (MedicNotFoundException e) {
        cout << "La siguiente excepción se ha capturado correctamente:" << endl;
        cout << e.msg() << endl;
    }
    
    // La fecha no es válida
    /*try {
        c.pideConsulta("Paciente 1", "Juan Carlos", Date(66, 12, 05));
    } catch (InvalidDateException e) {
        cout << e.msg() << endl;
    }*/
}

void test_next_patient() {
    
    Clinic c;
    
    c.nuevoMedico("Medico 1");
    
    // Insertar unas cuantas citas
    c.pideConsulta("Paciente 1", "Medico 1", Date(1, 1, 1));
    c.pideConsulta("Paciente 1", "Medico 1", Date(2, 1, 1));
    // estos van en el mismo dia...
    c.pideConsulta("Paciente 2", "Medico 1", Date(3, 2, 1));
    c.pideConsulta("Paciente 3", "Medico 1", Date(3, 3, 1));
    c.pideConsulta("Paciente 4", "Medico 1", Date(3, 4, 1));
    c.pideConsulta("Paciente 5", "Medico 1", Date(3, 5, 1));
    // end...
    c.pideConsulta("Paciente 6", "Medico 1", Date(4, 1, 1));
    
    cout << "Was: " << c.siguientePaciente("Medico 1") << endl;
    assert(c.siguientePaciente("Medico 1") == "Paciente 1");
    c.atiendeConsulta("Medico 1");
    
    cout << "Was: " << c.siguientePaciente("Medico 1") << endl;
    assert(c.siguientePaciente("Medico 1") == "Paciente 1");
    c.atiendeConsulta("Medico 1");
    
    cout << "Was: " << c.siguientePaciente("Medico 1") << endl;
    assert(c.siguientePaciente("Medico 1") == "Paciente 2");
    c.atiendeConsulta("Medico 1");
    assert(c.siguientePaciente("Medico 1") == "Paciente 3");
}

void test_treat_patient() {
    
}

void test_list_patients() {
    
    Clinic c;
    
    c.nuevoMedico("Medico 1");
    
    // Insertar unas cuantas citas
    c.pideConsulta("Paciente 1", "Medico 1", Date(1, 1, 1));
    c.pideConsulta("Paciente 1", "Medico 1", Date(2, 1, 1));
    // estos van en el mismo dia...
    c.pideConsulta("Paciente 2", "Medico 1", Date(3, 2, 1));
    c.pideConsulta("Paciente 3", "Medico 1", Date(3, 3, 1));
    c.pideConsulta("Paciente 4", "Medico 1", Date(3, 4, 1));
    c.pideConsulta("Paciente 5", "Medico 1", Date(3, 5, 1));
    // end...
    c.pideConsulta("Paciente 6", "Medico 1", Date(4, 1, 1));
    
    // Debería devolver un paciente
    //list<Patient> l_1 = c.listaPacientes("Ana María", Date(23, 12, 05));
    //cout << "Was: " << l_1.size() << endl;
    //assert(l_1.size() == 1);
    
    // Debería devolver una lista vacía
    list<Patient> l_2 = c.listaPacientes("Medico 1", Date(3, 0, 0));
    assert(l_2.size() == 4);
}

#endif /* test_clinic_h */


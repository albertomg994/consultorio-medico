//
//  test_appointment.cpp
//  T10-Juez-I
//
//  Created by Alberto Miedes on 18/5/16.
//  Copyright © 2016 Alberto Miedes. All rights reserved.
//

#ifndef test_appointment_h
#define test_appointment_h

#include <stdio.h>
#include "Appointment.h"
#include "Date.h"

using namespace std;

using Patient = std::string;   // Patient type

void test_constructor();
void test_getters();
void test_to_string();

void test_appointment() {
    
    /*
    test_constructor();
    test_getters();
    test_to_string();*/
    
    cout << "Testing Appointment" << endl;
    
    // Test case 1
    bool test_case_1 = false;
    Patient paciente_1("Paciente 1");
    
    //cout << "1";
    
    Date date_1(10, 10, 10);
    
    //cout << "2";
    
    Appointment app(paciente_1, date_1);
    
    //cout << "3";
    
    if ( (app.patient() == "Paciente 1") &&
         (app.date().to_string() == "D: 10 h: 10 m: 10")
        ) test_case_1 = true;

    // Test case 2
    /*bool test_case_2 = false;
    Date bad_date(0, 10, 10);
    try {
        Appointment bad_app(paciente_1, bad_date);
    } catch (InvalidDateException e) {
        test_case_2 = true;
    }*/
    
    if (test_case_1) cout << ".";
    else cout << "F";
    
    //if (test_case_2) cout << ".";
    //else cout << "F";
    
    cout << endl;
}

/*void test_constructor() {
    
    cout << "Testing Appointment constructors" << endl;
    
    Patient pac = "Paciente 1";
    Date date(10, 10, 10);
    
    Appointment app(pac, date);
    
}

void test_getters() {
    
}

void test_to_string() {
    
}*/

#endif
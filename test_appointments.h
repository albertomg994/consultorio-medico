//
//  test_appointments.cpp
//  T10-Juez-I
//
//  Created by Alberto Miedes on 18/5/16.
//  Copyright © 2016 Alberto Miedes. All rights reserved.
//

#ifndef test_appointments_h
#define test_appointments_h

#include <stdio.h>
#include "Appointment.h"
#include "Appointments.h"

using namespace std;

void test_appointments() {

    cout << "Testing Appointments" << endl;
    
    Appointments apps;
    
    // test case 1 - test insertions
    assert(apps.appointments().size() == 0);
    
    Appointment app_1("Paciente 1", Date(10, 10, 10));
    Appointment app_2("Paciente 2", Date(13, 10, 10));
    Appointment app_3("Paciente 3", Date(11, 10, 10));
    Appointment app_4("Paciente 4", Date(7, 10, 10));
    Appointment app_5("Paciente 5", Date(11, 10, 10));
    
    apps.new_appointment(app_1);
    
    assert(apps.appointments().size() == 1);
    assert(apps.get_appointments_on_date(Date(10, 10, 10)).size() == 1);
    
    apps.new_appointment(app_2);
    apps.new_appointment(app_3);
    apps.new_appointment(app_4);
    
    bool aux = false;
    try {
        apps.new_appointment(app_5);
    } catch (DateAlreadyTakenException e) {
        aux = true;
    }
    assert(aux);
    
    assert(apps.appointments().size() == 4);
    assert(apps.get_appointments_on_date(Date(11, 10, 10)).size() == 1);
    
    // test case 2 - test next & pop
    
    assert(apps.next_appointment().patient() == "Paciente 4");
    assert(apps.next_appointment().date() == Date(7, 10, 10));
    
    apps.pop_appointment();
    
    assert(apps.appointments().size() == 3);
    
    assert(apps.next_appointment().patient() == "Paciente 1");
    assert(apps.next_appointment().date() == Date(10, 10, 10));
    
    // test case 3 - get_appointments_on_date
    
    Appointment app_6("Paciente 7", Date(12, 15, 18));
    Appointment app_7("Paciente 8", Date(12, 16, 19));
    Appointment app_8("Paciente 9", Date(12, 17, 20));
    
    apps.new_appointment(app_6);
    apps.new_appointment(app_7);
    apps.new_appointment(app_8);
    
    assert(apps.get_appointments_on_date(Date(12, 20, 23)).size() == 3);
    assert(apps.get_appointments_on_date(Date(12, 21, 24)).size() == 3);
    assert(apps.get_appointments_on_date(Date(12, 22, 25)).size() == 3);
    
}

#endif
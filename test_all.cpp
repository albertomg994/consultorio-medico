//
//  test_all.cpp
//  T10-Juez-I
//
//  Created by Alberto Miedes on 18/5/16.
//  Copyright © 2016 Alberto Miedes. All rights reserved.
//

#include "test_date.h"
#include "test_appointment.h"
#include "test_appointments.h"
#include "test_clinic.h"

int main(void) {
    test_date();
    test_appointment();
    test_appointments();
    test_clinic();
}
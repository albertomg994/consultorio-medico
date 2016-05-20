//
//  test_date.h
//  T10-Juez-I
//
//  Created by Alberto Miedes on 18/5/16.
//  Copyright © 2016 Alberto Miedes. All rights reserved.
//

#ifndef test_date_h
#define test_date_h

#include <iostream>
#include <cassert>
#include "Date.h"

using namespace std;

void test_constructor();

void test_date() {
    
    test_constructor();
}

void test_constructor() {
    
    bool good_date = false, bad_day = false, bad_hour = false, bad_minute = false;
    
    cout << "Testing Date constructors:" << endl;
    
    // Trying to create a valida date
    try {
        Date valid_date(10, 10, 10);
        good_date = true;
    } catch (InvalidDateException e) {
        good_date = false;
    }
    
    // Trying to create a date with invalid day
    try {
        // Date (day, hour, minute)
        Date bad_day_date(0, 10, 10);
    } catch (InvalidDateException e) {
        bad_day = true;
    }
    
    // Trying to create a date with invalid hour
    try {
        Date bad_hour_date(10, 32, 10);
    } catch (InvalidDateException e) {
        bad_hour = true;
    }
    
    // Trying to create a date with invalid minute
    try {
        Date bad_day_date(10, 10, 70);
    } catch (InvalidDateException e) {
        bad_minute = true;
    }
    
    if (good_date) cout << ".";
    else cout << "F";
    
    if (bad_day) cout << ".";
    else cout << "F";
    
    if (bad_hour) cout << ".";
    else cout << "F";
    
    if (bad_minute) cout << ".";
    else cout << "F";
    
    cout << endl;
}

#endif
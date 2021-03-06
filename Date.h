//
//  Date.h
//  T10-Juez-I
//
//  Created by Alberto Miedes on 13/5/16.
//  Copyright © 2016 Alberto Miedes. All rights reserved.
//

#ifndef Date_h
#define Date_h

#include "ClinicException.h"
#include <iostream>
#include <string>

using namespace std;

/**
 * This exception is thrown when attempting to call Date constructor with an
 * invalid combination of day-hour-minute
 */
class InvalidDateException : public ClinicException {
public:
    InvalidDateException() : ClinicException("Los datos de la fecha no son válidos") {};
};

/**
 * Date class. Manages dates in the clinic system.
 */
class Date {
private:

    unsigned int _day;
    unsigned int _hour;
    unsigned int _minute;

    /**
     * NOTE: this method could be much more complicated
     * Complexity: O(1)
     *
     * @return true if day-hour-minute combination 'makes sense'
     */
    static bool valid_date(unsigned int d, unsigned int h, unsigned int m) {
        return valid_day(d) && valid_hour(h) && valid_minute(m);
    }

    static bool valid_day(unsigned int day) {
        return (day >= 1 && day <= 31);
    }

    static bool valid_hour(unsigned int hour) {
        return (hour <= 23);
    }

    static bool valid_minute(unsigned int minute) {
        return (minute <= 59);
    }

public:

    /**
     * Constructor
     * Complexity: O(1)
     *
     * @throws InvalidDateException if trying to create a not-coherent date
     * according tho the criteria in bool valid(d,h,m) method.
     */
    Date(unsigned int day, unsigned int hour, unsigned int minute) {
        if (!valid_date(day, hour, minute)) {
            cout << "Tried to create this date: " << day << " " << hour << ":" << minute << endl;
            throw InvalidDateException();
        }
        _day = day; _hour = hour; _minute = minute;
    }

    // Getters
    unsigned int day()    const { return _day;    }
    unsigned int hour()   const { return _hour;   }
    unsigned int minute() const { return _minute; }

    // Setters
    void set_day (unsigned int d) {
        if (!valid_date(d, _hour, _minute)) throw InvalidDateException();
        _day = d;
    }

    void set_hora(unsigned int h) {
        if (!valid_date(_day, h, _minute)) throw InvalidDateException();
        _hour = h;
    }

    void set_min (unsigned int m) {
        if (!valid_date(_day, _hour, m)) throw InvalidDateException();
        _minute = m;
    }

    // Others
    string to_string() const {
        return "D: " + std::to_string(_day) +
        " h: " + std::to_string(_hour) +
        " m: " + std::to_string(_minute);
    }

    /***********************************************************/
    /*                      Operators                          */
    /***********************************************************/

    bool operator<(const Date &other) const {
        if (_day < other.day()) return true;
        else if (_day > other.day()) return false;
        else { // _day == other.day()
            if (_hour < other.hour()) return true;
            else if (_hour > other.hour()) return false;
            else { // _hour == other.hour()
                return _minute < other.minute();
            }
        }
    }

    bool operator==(const Date &other) const {
        return (_day == other.day()) &&
               (_hour == other.hour()) &&
               (_minute == other.minute());
    }

    bool operator>(const Date &other) const {
        if (_day > other.day()) return true;
        else if (_day < other.day()) return false;
        else { // _day == other.day()
            if (_hour > other.hour()) return true;
            else if (_hour < other.hour()) return false;
            else { // _hour == other.hour()
                return _minute > other.minute();
            }
        }
    }
};


ostream &operator<<(ostream &output, const Date &d ) {
    output << d.to_string();
    return output;
}

istream &operator>>(istream  &input, Date &d) {
    unsigned int day, hour, minute;
    input >> day >> hour >> minute;
    d.set_day(day); d.set_hora(hour); d.set_min(minute);
    return input;
}

#endif /* Date_h */

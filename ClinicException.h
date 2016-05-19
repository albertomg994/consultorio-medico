//
//  ClinicException.h
//  T10-Juez-I
//
//  Created by Alberto Miedes on 14/5/16.
//  Copyright © 2016 Alberto Miedes. All rights reserved.
//

#ifndef ClinicException_h
#define ClinicException_h

#include <string>

using namespace std;

/**
 * A generic exception class with message for this exercise
 */
class ClinicException {
public:
    ClinicException() {}
    ClinicException(const string &msg) : _msg(msg) {}
    
    const string msg() const { return _msg; }
    
    friend ostream &operator<<(ostream &out, const ClinicException &e);
protected:
    string _msg;
};

inline ostream &operator<<(ostream &out, const ClinicException &e) {
    out << e._msg;
    return out;
}

/**
 * Thrown when trying to access a medic which is not present in the
 * clinic.
 */
class MedicNotFoundException : public ClinicException {
public:
    MedicNotFoundException() : ClinicException("Medico no existente") {};
};



#endif /* ClinicException_h */

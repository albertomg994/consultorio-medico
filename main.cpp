//
//  main.cpp
//  T10-Juez-I
//
//  Created by Alberto Miedes on 13/5/16.
//  Copyright © 2016 Alberto Miedes. All rights reserved.
//

#include <iostream>
#include <string>
#include <list>
#include "Clinic.h"
#include "Date.h"
#include "ClinicIO.h"

using namespace std;

using Medic = string;     // Medic type
using Patient = string;   // Patient type

int main(int argc, const char * argv[]) {

    unsigned int num_ops;
    string operacion;

    Clinic c;

    // Read number of operations in first case
    cin >> num_ops;
    cin.ignore();

    // Para cada caso
    while (!cin.eof()) {

        for (int i = 0; i < num_ops; i++) {

            cin >> operacion;

            if (operacion == "nuevoMedico") {
                ClinicIO::nuevoMedico(c);
            }

            else if (operacion == "pideConsulta") {
                ClinicIO::pideConsulta(c);
            }

            else if (operacion == "atiendeConsulta") {
                ClinicIO::atiendeConsulta(c);
            }

            else if (operacion == "listaPacientes") {
                ClinicIO::listaPacientes(c);
            }

            else if (operacion == "siguientePaciente") {
                ClinicIO::siguientePaciente(c);
            }

            else {
                ClinicIO::operacionNoValida();
            }

            cin.ignore();

        }

        // Each case ends with six -
        cout << "------" << endl;

        // Read number of operations in next case (if exists)
        cin >> num_ops;
        cin.ignore();
    }

    return 0;
}

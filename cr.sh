#!/bin/sh

#  cr.sh
#  T10-Juez-I
#
#  Created by Alberto Miedes on 20/5/16.
#  Copyright © 2016 Alberto Miedes. All rights reserved.

g++ -std=c++11 main.cpp -o clinic
./clinic < test/test-1.in > test/test-1.out
./clinic < test/test-2.in > test/test-2.out
./clinic < test/test-3.in > test/test-3.out
rm clinic
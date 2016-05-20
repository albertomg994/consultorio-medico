# *'Consultorio Médico'*

A project developed during the *Data Structures and Algorithms* (EDA) course to
practice with Hash Maps and Tree Maps.

## Compile instructions

```bash
g++ -std=c++11 main.cpp -o clinic
```

## Test instructions

The `test` directory contains test cases for the exercise.

**To run a specific test case, compile and then:**

```bash
./clinic < test/test-1.in > test/test-1.out
./clinic < test/test-2.in > test/test-2.out
./clinic < test/test-3.in > test/test-3.out
```

The `*.out.sample` files under the `test` directory contain the expected output
for each one of the tests.

**To compile the project and run all the tests:**

```bash
# Output files will be generated into test/test-X.out, (X = nº test)
./cr.sh
```

## License

* Some files (`TreeMap.h`, `Stack.h`, `Exceptions.h`) are property of Marco Antonio
Gómez Martín and have **copyright**. This files were provided during the course so
students could use them in their exercises.

* `prob-1001l.pdf` was written by Isabel Pita, and contains the instructions for the
exercise. It is also under **copyright**.

* All the other files were written by me (Alberto Miedes). These ones are under the
**MIT license**.

 ```
 Copyright (c) 2016 Alberto Miedes Garcés

 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in the
 Software without restriction, including without limitation the rights to use,
 copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
 Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 ```

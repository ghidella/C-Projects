# Personal projects for C++ study

## [Login and Register](https://github.com/ghidella/cpp-projects/tree/main/login_registration)
Simple cross-platform login and register program with little features.
### Instructions
#### Linux
In linux, compile with:
```bash
g++ -o program login_registration.cpp
```
And run using:
```bash
./program
```

##### Windows
In windows, compile with:
```bash
g++ login_registration.cpp -o program.exe
```
This will create an executable file program.exe, you can run just clicking on it or running:
```bash
./program.exe
```

## [Insertion Sort SFML](https://github.com/ghidella/cpp-projects/tree/main/insertion_sort)
Basic animation of the insertion sort algorithm using the [SFML library](https://www.sfml-dev.org/).
### Instructions
In windows, compile with:
```bash
g++ -Isrc/include -c main.cpp
```
Now, you must link the compiled file to the SFML libraries in order to get the final executable with the following command:
```bash
g++ main.o -o insertionSort -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system
```
Run it with:
```bash
./insertionSort.exe
```

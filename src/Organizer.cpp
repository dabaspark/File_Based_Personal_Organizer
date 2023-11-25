// Organizer.cpp
#include "include/Organizer.h"
#include <iostream>

Organizer::Organizer() {
    loadFromFile(); // Load data from files when the program starts
}

void Organizer::loadFromFile() {
    // Implement loading data from files
    // ...
}

void Organizer::saveToFile() {
    // Implement saving data to files
    // ...
}

void Organizer::run() {
    // Implement the console-based user interface and program flow
    // ...
}

int main() {
    Organizer organizer;
    organizer.run();

    return 0;
}

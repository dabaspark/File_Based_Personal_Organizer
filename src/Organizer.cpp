// Organizer.cpp
#include "include/Organizer.h"
#include <iostream>

Organizer::Organizer(const std::string& taskFilename, const std::string& appointmentFilename)
    : taskManager(taskFilename), appointmentManager(appointmentFilename) {
    // Constructor implementation
}

Organizer::~Organizer() {
    // Destructor implementation
    // call destructor for taskManager and appointmentManager
    taskManager.~TaskManager();
    appointmentManager.~AppointmentManager();
}

void Organizer::displayMainMenu() {
    int choice;

    do {
        print_menu_header("Main Menu", true); // Clear the console = true
        std::cout << "1. Task Menu\n";
        std::cout << "2. Appointment Menu\n";
        std::cout << "3. Quit\n";

        choice = getValidChoice(1, 3);

        switch (choice) {
            case 1:
                taskManager.runWindow_Task();
                break;
            case 2:
                appointmentManager.runWindow_Appointment();
                break;
            case 3:
                std::cout << "Exiting program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 3.\n";
        }
    } while (choice != 3);
}



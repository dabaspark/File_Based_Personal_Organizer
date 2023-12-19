// Organizer.cpp
#include "include/Organizer.h"
#include <iostream>

Organizer::Organizer(const std::string& taskFilename, const std::string& appointmentFilename, const std::string& noteFilename)
    : taskManager(taskFilename), appointmentManager(appointmentFilename), noteManager(noteFilename) {
    // Constructor implementation
    unsavedChanges_organizer = false;
}

Organizer::~Organizer() {
    // Destructor implementation
    // call destructor for taskManager and appointmentManager
    taskManager.~TaskManager();
    appointmentManager.~AppointmentManager();
    noteManager.~NoteManager();
}

void Organizer::displayMainMenu() {
    int choice;

    do {
        print_menu_header("Main Menu", true); // Clear the console = true
        unsavedChanges_organizer = taskManager.unsavedChanges || appointmentManager.unsavedChanges || noteManager.unsavedChanges;

        std::cout << "Number of Tasks: " << taskManager.tasks.size() <<", "
            << "Number of Appointments: " << appointmentManager.appointments.size() << ", " 
            << "Number of Notes: " << noteManager.notes.size() << "\n" 
            << "File Status: " << (unsavedChanges_organizer ? "\033[1;31mNew Changes Not Saved to the File!\033[0m" : "Up to Date") << "\n";

        std::cout << "====================\n";
        std::cout << "1. Task Menu\n";
        std::cout << "2. Appointment Menu\n";
        std::cout << "3. Note Menu\n";

        std::cout << "4. Save Changes to File\n";
        std::cout << "5. Save and Quit\n";
        std::cout << "6. Quit without Saving\n";

        choice = getValidChoice(1, 6);

        switch (choice) {
            case 1:
                taskManager.runWindow_Task();
                break;
            case 2:
                appointmentManager.runWindow_Appointment();
                break;
            case 3:
                noteManager.runWindow_Note();
                break;

            case 4:
                taskManager.saveTasksToFile();
                appointmentManager.saveAppointmentsToFile();
                taskManager.unsavedChanges = false;
                appointmentManager.unsavedChanges = false;
                unsavedChanges_organizer = false;
                std::cout << "Changes Saved.\n";
                break;
            case 5:
                taskManager.saveTasksToFile();
                appointmentManager.saveAppointmentsToFile();
                taskManager.unsavedChanges = false;
                appointmentManager.unsavedChanges = false;
                unsavedChanges_organizer = false;
                std::cout << "Changes Saved. Quitting...\n";
                break;
            case 6:
                if(unsavedChanges_organizer) {
                    std::cout << "Changes not saved. Are you sure you want to quit? (y/n): ";
                    char confirm;
                    std::cin >> confirm;
                    cin.ignore(1, '\n');
                    if(confirm == 'y' || confirm == 'Y') {
                        std::cout << "Exiting program without saving....\n";
                        return;
                    } else {
                        choice = 0; // Reset the choice to display the menu again
                        std::cout << "Continuing the program...\n";
                        return;
                    }
                } else {
                    std::cout << "Exiting program.\n";
                }
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 6.\n";
        }
    } while (choice != 5 && choice != 6);
}



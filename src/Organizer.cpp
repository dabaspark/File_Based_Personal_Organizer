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
}

void Organizer::displayMainMenu() {
    int choice;

    do {
        // Get the upcoming number of tasks and appointments within three days
        auto remindersInfo = Reminders();
        int tasksWithinThreeDays = std::get<0>(remindersInfo);
        int appointmentsWithinThreeDays = std::get<1>(remindersInfo);
        std::string formattedCurrentTime = std::get<2>(remindersInfo);

        print_menu_header("Main Menu", true); // Clear the console = true
        unsavedChanges_organizer = taskManager.unsavedChanges || appointmentManager.unsavedChanges || noteManager.unsavedChanges;

        std::cout << "Today's Date: " << formattedCurrentTime << "\n";
        std::cout << "----------------------\n";
        std::cout << "Organizer Status:\n";
        std::cout << "Number of Tasks: " << taskManager.tasks.size() <<", "
            << "Number of Appointments: " << appointmentManager.appointments.size() << ", " 
            << "Number of Notes: " << noteManager.notes.size() << "\n" 
            << "File Status: " << (unsavedChanges_organizer ? "\033[1;31mNew Changes Not Saved to the File!\033[0m" : "Up to Date") << "\n";

        // Display the upcoming number of tasks and appointments within three days
        std::cout << "----------------------\n";
        std::cout << "Reminders:\n";
        if (tasksWithinThreeDays == 0 && appointmentsWithinThreeDays == 0) {
            std::cout << "\033[1;32mNo reminders for the upcoming three days.\033[0m\n";
        } else {
            std::cout << "Upcoming Tasks (within 3 days): ";
            if (tasksWithinThreeDays > 0) {
                std::cout << "\033[1;31m" << tasksWithinThreeDays << "\033[0m";
            } else {
                std::cout << tasksWithinThreeDays;
            }
            std::cout << "\n";

            std::cout << "Upcoming Appointments (within 3 days): ";
            if (appointmentsWithinThreeDays > 0) {
                std::cout << "\033[1;31m" << appointmentsWithinThreeDays << "\033[0m";
            } else {
                std::cout << appointmentsWithinThreeDays;
            }
            std::cout << "\n";
        }

        std::cout << "====================\n";
        std::cout << "1. Task Menu\n";
        std::cout << "2. Appointment Menu\n";
        std::cout << "3. Note Menu\n";

        // Print "4. Display Reminders" in red if there are reminders
        std::cout << "4. ";
        if (tasksWithinThreeDays > 0 || appointmentsWithinThreeDays > 0) {
            std::cout << "\033[1;31mDisplay Reminders\033[0m";
        } else {
            std::cout << "Display Reminders";
        }
        std::cout << "\n";

        std::cout << "5. ";
        if (unsavedChanges_organizer) {
            std::cout << "\033[1;31mSave Changes to File\033[0m";
        } else {
            std::cout << "Save Changes to File";
        }
        std::cout << "\n";

        std::cout << "6. Save and Quit\n";
        std::cout << "7. Quit without Saving\n";

        choice = getValidChoice(1, 7);

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
                displayReminders();
                break;
            case 5:
                taskManager.saveTasksToFile();
                appointmentManager.saveAppointmentsToFile();
                noteManager.saveNotesToFile();
                taskManager.unsavedChanges = false;
                appointmentManager.unsavedChanges = false;
                noteManager.unsavedChanges = false;
                unsavedChanges_organizer = false;
                std::cout << "Changes Saved.\n";
                break;
            case 6:
                taskManager.saveTasksToFile();
                appointmentManager.saveAppointmentsToFile();
                noteManager.saveNotesToFile();
                taskManager.unsavedChanges = false;
                appointmentManager.unsavedChanges = false;
                noteManager.unsavedChanges = false;
                unsavedChanges_organizer = false;
                std::cout << "Changes Saved. Quitting...\n";
                break;
            case 7:
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
                std::cout << "Invalid choice. Please enter a number between 1 and 7.\n";
        }
    } while (choice != 6 && choice != 7);
}


std::tuple<int, int, std::string> Organizer::Reminders() const {
    // Get the current date and time
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Convert the current time to the "YYYY-MM-DD" format
    std::tm* currentTm = std::localtime(&currentTime);
    std::stringstream currentTimeStream;
    currentTimeStream << std::put_time(currentTm, "%Y-%m-%d");
    std::string formattedCurrentTime = currentTimeStream.str();

    // Calculate the next three days from the current date
    std::chrono::system_clock::time_point threeDaysLater = now + std::chrono::hours(24 * 3);
    std::time_t threeDaysLaterTime = std::chrono::system_clock::to_time_t(threeDaysLater);

    // Convert the three days later time to the "YYYY-MM-DD" format
    std::tm* threeDaysLaterTm = std::localtime(&threeDaysLaterTime);
    std::stringstream threeDaysLaterStream;
    threeDaysLaterStream << std::put_time(threeDaysLaterTm, "%Y-%m-%d");
    std::string formattedThreeDaysLater = threeDaysLaterStream.str();

    // Counters for tasks and appointments within three days
    int tasksWithinThreeDays = std::count_if(taskManager.tasks.begin(), taskManager.tasks.end(),
        [&](const Task& task) {
            return !task.completed && task.deadline > formattedCurrentTime && task.deadline <= formattedThreeDaysLater;
        });

    int appointmentsWithinThreeDays = std::count_if(appointmentManager.appointments.begin(), appointmentManager.appointments.end(),
        [&](const Appointment& appointment) {
            return appointment.date > formattedCurrentTime && appointment.date <= formattedThreeDaysLater;
        });

    // Return the number of tasks and appointments within three days and formatted current time
    return {tasksWithinThreeDays, appointmentsWithinThreeDays, formattedCurrentTime};
}


void Organizer::displayReminders() const{
    print_menu_header("Main Manu >> Reminders", true);

    // Get the current date and time
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Convert the current time to the "YYYY-MM-DD" format
    std::tm* currentTm = std::localtime(&currentTime);
    std::stringstream currentTimeStream;
    currentTimeStream << std::put_time(currentTm, "%Y-%m-%d");
    std::string formattedCurrentTime = currentTimeStream.str();

    // Calculate the next three days from the current date
    std::chrono::system_clock::time_point threeDaysLater = now + std::chrono::hours(24 * 3);
    std::time_t threeDaysLaterTime = std::chrono::system_clock::to_time_t(threeDaysLater);

    // Convert the three days later time to the "YYYY-MM-DD" format
    std::tm* threeDaysLaterTm = std::localtime(&threeDaysLaterTime);
    std::stringstream threeDaysLaterStream;
    threeDaysLaterStream << std::put_time(threeDaysLaterTm, "%Y-%m-%d");
    std::string formattedThreeDaysLater = threeDaysLaterStream.str();

    // Display reminders for tasks
    std::cout << "\nUpcoming Task Reminders:\n";
    for (const Task& task : taskManager.tasks) {
        if (!task.completed && task.deadline > formattedCurrentTime && task.deadline <= formattedThreeDaysLater) {
            std::cout << "Task: " << task.title << "\n"
                      << "Deadline: " << task.deadline << "\n";
        }
    }

    // Display reminders for appointments
    std::cout << "\nUpcoming Appointment Reminders:\n";
    for (const Appointment& appointment : appointmentManager.appointments) {
        if (appointment.date > formattedCurrentTime && appointment.date <= formattedThreeDaysLater) {
            std::cout << "Appointment: " << appointment.title << "\n"
                      << "Date and Time: " << appointment.date << " " << appointment.time << "\n";
        }
    }

    print_menu_tail("Main Menu", true);
}

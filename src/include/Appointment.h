// Appointment.h
#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
#include <vector>

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>  // for date and time operations
#include <cctype>  //for task keywork search // for character classification functions
#include <sstream> // for string stream operations
#include <ctime>    // for time operations
#include <iomanip>  // for date and time formatting
#include <limits>  // for limiting user input in display menu (error handling)
#include <thread> // for std::this_thread::sleep_for
#include <chrono> // for std::chrono::seconds

#include "Utilities.h"

using namespace std;

// Define the structure for a task
struct Appointment {
    string title;       // Title of the Appointment
    string note;        // Notes for the Appointment
    string date;        // Date of the Appointment
    string time;        // Time of the Appointment
    string creationDate; // Creation date of the Appointment
};

class AppointmentManager {
public:
    // Constructor
    AppointmentManager(const std::string& filename);

    // Destructor
    ~AppointmentManager();

    // Function to add a new Appointment
    void addAppointment();

    // Function to display all Appointment
    void displayAppointments();

    // Function to edit an Appointment
    void editAppointment();

    // Function to delete a Appointment
    void deleteAppointment();

    // Function to mark an Appointment as completed
    void markAppointmentCompleted();

    // Function to search for an Appointment
    void searchAppointmentsByKeyword() const;

    // Function to save Appointments to a file
    void saveAppointmentsToFile() const;

    // Function to load Appointments from a file
    void loadAppointmentsFromFile() ;

    // Function to run the Appointment management window
    void runWindow_Appointment();

    // Function to sort tasks
    void listAndSortAppointments();

private:
    std::vector<Appointment> appointments;
    std::string appointment_filename;
    bool unsavedChanges;

    // Utility functions for entering Appointment details
    string enterAppointmentTitle() const;
    string enterAppointmentNote() const;
    string enterAppointmentDate() const;
    string enterAppointmentTime() const;

    // Utility function for editAppointment function
    std::string trim(const std::string& str);

    // utilitis for listAndSortAppointments
    void displayAppointmentsDetailed(const std::vector<Appointment>& appointments, bool clearScreen);
};

#endif // APPOINTMENT_H

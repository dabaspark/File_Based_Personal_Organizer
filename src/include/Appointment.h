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
#include <iomanip>
#include <map>
#include <unordered_map>  
#include <algorithm>

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
    bool unsavedChanges;
    std::vector<Appointment> appointments;
    
    // Constructor
    AppointmentManager(const std::string& filename);

    // Destructor
    ~AppointmentManager();

    // Function to add a new Appointment
    void addAppointment();

    // Function to display all Appointment
    void displayAppointments();

    // Function to show upcoming Appointment in daily, weekly, monthly format
    void displayUpcomingAppointments();

    // Function to edit an Appointment
    void editAppointment();

    // Function to delete a Appointment
    void deleteAppointment();

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
    std::string appointment_filename;

    // Utility functions for entering Appointment details
    string enterAppointmentTitle() const;
    string enterAppointmentNote() const;
    string enterAppointmentDate(bool accept_past) const;
    string enterAppointmentTime() const;

    // utilitis for listAndSortAppointments
    void displayAppointmentsDetailed(const std::vector<Appointment>& appointments, bool clearScreen);

    // Utility functions for displayUpcomingAppointments
    void displayAppointmentsDaily(const std::string& date) const;
    void displayAppointmentsWeekly(const std::string& date) const;
    void displayAppointmentsMonthly(const std::string& date) const;
    std::string enterMonth() const;
    bool isValidMonthFormat(const std::string& month) const;
    void displayUpcomingAppointmentsDetailed(const std::vector<Appointment>& appointments, const std::string& type) const;
    std::vector<Appointment> sortAppointmentsByDate(const std::vector<Appointment>& appointments);
    void displayDailyAppointments(const std::vector<Appointment>& appointments) const;
    void displayWeeklyAppointments(const std::vector<Appointment>& appointments) const;
    void displayMonthlyAppointments(const std::vector<Appointment>& appointments) const;
};

#endif // APPOINTMENT_H

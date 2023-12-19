// Organizer.h
#ifndef ORGANIZER_H
#define ORGANIZER_H
#include "Task.h"
#include "Appointment.h"
#include "Note.h"
#include "Utilities.h"
#include <algorithm>  

class Organizer {
public:
    // Constructor
    Organizer(const std::string& taskFilename, const std::string& appointmentFilename, const std::string& noteFilename);

    // Destructor
    ~Organizer();

    // Function to display the main menu
    void displayMainMenu();

    // Function to display reminders
    std::tuple<int, int, std::string> Reminders() const;
    void displayReminders() const;

private:
    TaskManager taskManager;
    AppointmentManager appointmentManager;
    NoteManager noteManager;
    bool unsavedChanges_organizer;
};

#endif // ORGANIZER_H

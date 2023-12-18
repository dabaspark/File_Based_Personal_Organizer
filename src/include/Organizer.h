// Organizer.h
#ifndef ORGANIZER_H
#define ORGANIZER_H
#include "Task.h"
#include "Appointment.h"
#include "Utilities.h"

class Organizer {
public:
    // Constructor
    Organizer(const std::string& taskFilename, const std::string& appointmentFilename);

    // Destructor
    ~Organizer();

    // Function to display the main menu
    void displayMainMenu();

private:
    TaskManager taskManager;
    AppointmentManager appointmentManager;
    bool unsavedChanges_organizer;
};

#endif // ORGANIZER_H

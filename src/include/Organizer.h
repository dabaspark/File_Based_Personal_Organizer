// Organizer.h
#ifndef ORGANIZER_H
#define ORGANIZER_H
#include "Task.h"
#include "Appointment.h"
#include "Note.h"
#include "Utilities.h"


class Organizer {
public:
    // Constructor
    Organizer(const std::string& taskFilename, const std::string& appointmentFilename, const std::string& noteFilename);

    // Destructor
    ~Organizer();

    // Function to display the main menu
    void displayMainMenu();

private:
    TaskManager taskManager;
    AppointmentManager appointmentManager;
    NoteManager noteManager;
    bool unsavedChanges_organizer;
};

#endif // ORGANIZER_H

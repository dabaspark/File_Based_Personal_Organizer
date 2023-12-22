#include "include/Organizer.h"

int main() {
    const std::string taskFilename = "storage/tasks.txt";
    const std::string appointmentFilename = "storage/appointments.txt";
    const std::string noteFilename = "storage/notes.txt";

    Organizer organizer(taskFilename, appointmentFilename, noteFilename);
    organizer.displayMainMenu();

    return 0;
}

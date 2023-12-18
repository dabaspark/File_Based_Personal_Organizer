//#include "include/Task.h"
#include "include/Organizer.h"

int main() {
    const std::string taskFilename = "storage/tasks.txt";
    const std::string appointmentFilename = "storage/appointments.txt";

    Organizer organizer(taskFilename, appointmentFilename);
    organizer.displayMainMenu();

    return 0;
}

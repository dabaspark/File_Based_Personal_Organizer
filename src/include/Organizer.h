// Organizer.h
#ifndef ORGANIZER_H
#define ORGANIZER_H

#include <vector>
#include "Task.h"
#include "Appointment.h"
#include "Note.h"

class Organizer {
public:
    Organizer();
    void loadFromFile();
    void saveToFile();
    void run();

private:
    std::vector<TaskNode> tasks;
    std::vector<Appointment> appointments;
    std::vector<Note> notes;
};

#endif // ORGANIZER_H

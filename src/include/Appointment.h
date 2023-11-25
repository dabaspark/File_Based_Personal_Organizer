// Appointment.h
#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
#include <vector>

struct Appointment {
    std::string title;
    std::string date;
    std::string time;
    std::string notes;
};

void addAppointment(std::vector<Appointment> &appointments);
void viewAppointments(const std::vector<Appointment> &appointments);
void editAppointment(std::vector<Appointment> &appointments, int index);
void deleteAppointment(std::vector<Appointment> &appointments, int index);

#endif // APPOINTMENT_H

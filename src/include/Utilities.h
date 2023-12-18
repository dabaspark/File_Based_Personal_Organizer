// Utilities.h
#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <string>
#include <sstream>
#include <limits>


// Function to validate and get user input as an integer within a specified range
int getValidChoice(int min, int max);


// Utilitis function for enterDate function
bool isValidDateFormat(const std::string& date);
bool isPast(const std::string& date);
bool isValidDate(int year, int month, int day);

// Utilitis function for enterTime function
bool isValidTimeFormat(const std::string& time);

// utilitis function for menu and printing
void print_menu_header(const std::string& header, bool clear_screen = true);
void print_menu_tail(const std::string& go_back_to, bool clear_screen = true);

// utilitis function for enterString function
std::string trim(const std::string& str);

#endif // UTILITIES_H
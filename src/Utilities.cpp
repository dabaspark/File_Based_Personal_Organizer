// Utilities.cpp

#include "include/Utilities.h"
#include <iomanip>
#include <chrono> // Include the necessary header file for std::chrono library


int getValidChoice(int min, int max) {
    int choice;
    std::string input;

    // Input validation loop
    while (true) {
        std::cout << "Enter your choice ("<< min <<"-"<< max <<"): ";
        std::getline(std::cin, input);

        std::stringstream ss(input);

        if (ss >> choice && ss.eof() && choice >= min && choice <= max) {
            // Successful conversion to integer and within the valid range
            break;
        }

        std::cout << "Invalid choice. Please enter a whole number between " << min << " and " << max << ".\n";
    }

    return choice;
}


// Utility function to check if the deadline is in the past
bool isPast(const std::string& date){


    std::tm deadlineDate = {};
    std::istringstream ss(date);

    // Parse the deadline components manually
    if (ss >> std::get_time(&deadlineDate, "%Y-%m-%d")) {
        // Check if the extracted date components are valid
        if (isValidDate(deadlineDate.tm_year + 1900, deadlineDate.tm_mon + 1, deadlineDate.tm_mday)) {
            // Get the current time
            auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

            // Compare the deadline date with the current date
            return std::mktime(&deadlineDate) < now;
        }
    }

    return false; // Invalid date format, handled separately
}

    // Check if the date components are valid
bool isValidDate(int year, int month, int day){
    // Some basic validation
    return (year >= 1900 && month >= 1 && month <= 12 && day >= 1 && day <= 31);
}

// Utility function to check if the date has a valid format (YYYY-MM-DD)
bool isValidDateFormat(const std::string& date){
    std::tm testDate = {};
    std::istringstream ss(date);

    // Parse the date components manually
    ss >> std::get_time(&testDate, "%Y-%m-%d");

    // Check if the entire input string is consumed and date components are valid
    return !ss.fail() && ss.eof() && isValidDate(testDate.tm_year + 1900, testDate.tm_mon + 1, testDate.tm_mday);
}


void print_menu_header(const std::string& header, bool clear_screen){
    if (clear_screen){
        std::system("clear");
    }
    std::cout << "====================\n";
    std::cout << header << "\n";
    std::cout << "====================\n";
}

void print_menu_tail(const std::string& go_back_to, bool clear_screen){
    // press any key to exit
    std::cout << "Press any key to go back to " << go_back_to << ".\n";
    std::cin.get();

    if (clear_screen){
        // Clear the console
        std::system("clear");
    }
}
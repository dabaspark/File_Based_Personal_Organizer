// Utilities.cpp

#include "include/Utilities.h"
#include <iomanip>
#include <chrono> // Include the necessary header file for std::chrono library
#include <regex> // Include the necessary header file for std::regex
#include <ctime>
#include <string>
#include <sstream>
#include <iostream>

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
    // press any key to go back to main menu
    std::cout << "------------------------------------------------\n";
    std::cout << "Press any key to go back to " << go_back_to << ": ";
    std::cin.get();

    if (clear_screen){
        std::system("clear");
    }
}


bool isValidTimeFormat(const std::string& time) {
    // Simplified time format allowing for single digits
    std::regex timeFormat(R"([0-2]?[0-9]:[0-5]?[0-9])");

    // Check if the entered time matches the updated format
    return std::regex_match(time, timeFormat);
}

// Function to trim whitespaces from both ends of a string
std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");
    return (start != std::string::npos && end != std::string::npos) ? str.substr(start, end - start + 1) : "";
}


std::string getDayOfWeek(const std::string& dateStr) {
    // Convert the input string to a time structure
    struct std::tm timeinfo = {};
    std::istringstream ss(dateStr);
    ss >> std::get_time(&timeinfo, "%Y-%m-%d");

    if (ss.fail()) {
        // Failed to parse the date string
        return "Invalid Date";
    }

    // Get the day of the week as an integer (0 = Sunday, 1 = Monday, ..., 6 = Saturday)
    int dayOfWeek = timeinfo.tm_wday;

    // Define an array of day names
    const char* dayNames[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    // Return the corresponding day name
    return dayNames[dayOfWeek];
}


std::tm convertStringToTm(const std::string& dateStr, const std::string& format) {
    std::tm tmDate = {};
    std::istringstream ss(dateStr);
    ss >> std::get_time(&tmDate, format.c_str());
    if (ss.fail()) {
        // Handle parsing failure, e.g., invalid date string
        throw std::runtime_error("Failed to parse date string");
    }
    return tmDate;
}

std::chrono::system_clock::time_point convertStringToTimePoint(const std::string& dateTimeStr, const std::string& format) {
    std::tm tmDateTime = {};
    std::istringstream ss(dateTimeStr);
    ss >> std::get_time(&tmDateTime, format.c_str());
    if (ss.fail()) {
        // Handle parsing failure, e.g., invalid date/time string
        throw std::runtime_error("Failed to parse date/time string");
    }

    // Convert std::tm to std::chrono::system_clock::time_point
    return std::chrono::system_clock::from_time_t(std::mktime(&tmDateTime));
}

std::string convertTmToString(const std::tm& timeStruct, const std::string& format) {
    std::stringstream ss;
    ss << std::put_time(&timeStruct, format.c_str());
    return ss.str();
}

// Helper function to check if the date format is "YYYY-M-D"
bool isValidYearMonthDayFormat(const std::string& date) {
    std::regex regexPattern(R"(\d{4}-\d{1,2}-\d{1,2})");
    return std::regex_match(date, regexPattern);
}

// Helper function to convert "YYYY-M-D" to "YYYY-MM-DD"
std::string convertToYYYYMMDDFormat(const std::string& date) {
    std::tm time = {};
    std::stringstream ss(date);
    ss >> std::get_time(&time, "%Y-%m-%d");

    if (ss.fail()) {
        return date; // Return the original date if conversion fails
    }

    std::ostringstream oss;
    oss << std::put_time(&time, "%Y-%m-%d");
    return oss.str();
}


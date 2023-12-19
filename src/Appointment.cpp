// Appointment.cpp
#include "include/Appointment.h"


// Constructor
AppointmentManager::AppointmentManager(const std::string& filename) : appointment_filename(filename) {
    loadAppointmentsFromFile();
    unsavedChanges = false;
}

// Destructor
AppointmentManager::~AppointmentManager() {
    // Clear the console
    std::system("clear");
}

void AppointmentManager::addAppointment() {
    
    print_menu_header("Main Menu >> Appointments Menu >> Add an Appointment", true); // Clear the console

    // Display information about the add Appointment process
    std::cout << "Add appointment:\n";
    std::cout << "Please enter the details for the new appointment.\n";
    std::cout << "You will be prompted for the title, note, date, and time.\n";
    std::cout << "---------------------------------------------\n";

    Appointment newAppointment;

    newAppointment.title = enterAppointmentTitle();
    newAppointment.note = enterAppointmentNote();
    newAppointment.date = enterAppointmentDate(false);
    newAppointment.time = enterAppointmentTime();

    // Get the current date and time
    auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    newAppointment.creationDate = ctime(&now); // Convert to string
    newAppointment.creationDate.pop_back(); // Remove the newline character

    // ask the user if they are sure they want to add the appointment
    char choice;
    cout << "Are you sure you want to add this appointment? (y/n): ";
    cin >> choice;
    cin.ignore(1, '\n');
    if (tolower(choice) != 'y' && tolower(choice) != 'Y') {
        cout << "Appointment not added.\n";
        return;
    }
    appointments.push_back(newAppointment);
    unsavedChanges = true;
    std::cout << "Appointment added successfully!\n";

    print_menu_tail("Appointments Menu", true); // Clear the console
}

void AppointmentManager::displayAppointments(){
    
    print_menu_header("Main Menu >> Appointments Menu >> Display Appointments", true); // Clear the console

    // ask the user to show it in Table format or normal format
    int choice;
    std::cout << "1. Detailed Format\n";
    std::cout << "2. Table Format\n";
    choice = getValidChoice(1, 2);

    std::cout << "The Appointments are:\n";
    std::cout << "-----------------------------------------------\n";
    if (choice == 2) {
        // Display appointments in detailed format
        displayAppointmentsDetailed(appointments, false);
    } else { 
        std::cout << "Appointments:\n";
        for (const Appointment& appointment : appointments) {
            std::cout << "Title: " << appointment.title << "\n";
            std::cout << "Note: " << appointment.note << "\n";
            std::cout << "Date: " << appointment.date << "\n";
            std::cout << "Time: " << appointment.time << "\n";
            std::cout << "Creation Date: " << appointment.creationDate << "\n";
            std::cout << "-----------------\n";
        }
    }

    print_menu_tail("Appointments Menu", true); // Clear the console
}

void AppointmentManager::displayUpcomingAppointments() {
    print_menu_header("Main Menu >> Appointments Menu >> View Upcoming Appointments in Daily/weekly/monthly Format", true); // Clear the console

    // Display options for viewing upcoming appointments
    std::cout << "View upcoming appointments in:\n";
    std::cout << "1. Daily Format\n";
    std::cout << "2. Weekly Format\n";
    std::cout << "3. Monthly Format\n";

    // Get the user input
    int viewOption = getValidChoice(1, 3);

    // sort appointments by date before showing
    appointments = sortAppointmentsByDate(appointments);

    switch (viewOption) {
        case 1: {
            std::cout << "Enter the date of the day you want to view.\n";
            std::string date = enterAppointmentDate(true);
            displayAppointmentsDaily(date);
            break;
        }
        case 2: {
            std::cout << "Enter the start date of the week you want to view.\n";
            std::string week = enterAppointmentDate(true); // Assuming user inputs the start date of the week
            displayAppointmentsWeekly(week);
            break;
        }
        case 3: {
            std::cout << "Enter the month you want to view (YYYY-MM).\n";
            std::string month = enterMonth(); 
            displayAppointmentsMonthly(month);
            break;
        }
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 3.\n"; // just in case, it will never comes here because of getValidChoice
    }

    print_menu_tail("Appointments Menu", true); // Clear the console
}



void AppointmentManager::listAndSortAppointments() {
    int sortOption;

    print_menu_header("Main Menu >> Appointments Menu >> List and Sort Appointments", true); // Clear the console

    // Display sorting options
    std::cout << "Sort appointments by:\n";
    std::cout << "1. Title\n";
    std::cout << "2. Date\n";
    std::cout << "3. Creation Date\n";

    // get the user input
    sortOption = getValidChoice(1, 3);

    // Make a copy of the original appointments vector
    std::vector<Appointment> originalAppointments = appointments;

    // Perform sorting based on user choice
    switch (sortOption) {
        case 1:
            std::sort(appointments.begin(), appointments.end(), [](const Appointment& a, const Appointment& b) {
                // Perform case-insensitive comparison
                return std::lexicographical_compare(
                    a.title.begin(), a.title.end(),
                    b.title.begin(), b.title.end(),
                    [](char c1, char c2) { return std::tolower(c1) < std::tolower(c2); }
                );
            });
            break;
        case 2:
            appointments = sortAppointmentsByDate(appointments);
            break;
        case 3:
            std::sort(appointments.begin(), appointments.end(), [](const Appointment& a, const Appointment& b) {
                return a.creationDate < b.creationDate;
            });
            break;
    }

    // Display sorted appointments in detailed format
    displayAppointmentsDetailed(appointments, false);

    // Ask the user for confirmation
    char choice;
    std::cout << "Are you sure you want to change the order of the appointments? (y/n): ";
    std::cin >> choice;
    cin.ignore(1, '\n');
    if (tolower(choice) != 'y' && tolower(choice) != 'Y') {
        // Revert to the original order
        appointments = originalAppointments;
        std::cout << "Order is not changed.\n";
        return;
    }

    std::cout << "Appointments order changed!\n";
    unsavedChanges = true;

    print_menu_tail("Appointment Menu", true); // Clear the console
}


void AppointmentManager::editAppointment() {
    string searchTitle;

    print_menu_header("Main Menu >> Appointments Menu >> Edit Appointments", true); // Clear the console
    
    // Display information about the edit Appointment process
    std::cout << "You will be prompted to enter the title of the appointment to be changed\n";
    std::cout << "Then, specify which field you want to edit.\n";
    std::cout << "---------------------------------------------\n";
    std::cout << "The List of the Appointments are:\n";
    std::cout << "---------------------------------------------\n";
    displayAppointmentsDetailed(appointments, false);

    // Get the title of the Appointment to be edited
    std::cout << "---------------------------------------------\n";
    cout << "Enter the title of the appointment you want to edit: ";

    getline(cin, searchTitle);
    
    // Trim whitespaces from the input title
    searchTitle = trim(searchTitle);

    auto it = find_if(appointments.begin(), appointments.end(), [&searchTitle](const Appointment& appointment) {
        return appointment.title == searchTitle;
    });


    if (it != appointments.end()) {
        Appointment editedAppointment = *it;  // Create a copy of the original appointment

        // Display editing options
        cout << "Edit Appointment:\n";
        cout << "1. Title\n";
        cout << "2. Note\n";
        cout << "3. Date\n";
        cout << "4. Time\n";
        cout << "5. All\n";

        int editOption;
        editOption = getValidChoice(1, 5);

        // Perform editing based on user choice
        switch (editOption) {
            case 1:
                editedAppointment.title = enterAppointmentTitle();
                break;
            case 2:
                editedAppointment.note = enterAppointmentNote();
                break;
            case 3:
                editedAppointment.date = enterAppointmentDate(false);
                break;
            case 4:
                editedAppointment.time = enterAppointmentTime();
                break;
            case 5:
                // If the user chooses to edit all fields, update all fields
                editedAppointment.title = enterAppointmentTitle();
                editedAppointment.note = enterAppointmentNote();
                editedAppointment.date = enterAppointmentDate(false);
                editedAppointment.time = enterAppointmentTime();
                break;
        }

        // Ask the user if they want to save changes
        char saveChoice;
        cout << "Are you sure you want to save the changes? (y/n): ";
        cin >> saveChoice;
        cin.ignore(1, '\n');
        if (tolower(saveChoice) == 'y') {
            // If the user chooses to save, update the original appointment
            *it = editedAppointment;
            cout << "Changes saved!\n";
            unsavedChanges = true;
        } else {
            // If the user chooses not to save, discard the changes
            cout << "Changes discarded.\n";
        }
    } else {
        cout << "Appointment not found.\n";
    }

    print_menu_tail("Appointments Menu", true); // Clear the console
}



void AppointmentManager::deleteAppointment() {
    string searchTitle;

    print_menu_header("Main Menu >> Appointments Menu >> Delete Appointments", true); // Clear the console
    
    // Display information about the delete Appointment process
    std::cout << "You will be prompted to enter the title of the appointment to be deleted\n";
    std::cout << "---------------------------------------------\n";
    std::cout << "The List of the Appointments are:\n";
    std::cout << "---------------------------------------------\n";

    displayAppointmentsDetailed(appointments, false);
    std::cout << "---------------------------------------------\n";
    cout << "Enter the title of the appointment you want to delete: ";

    getline(cin, searchTitle);

    auto it = find_if(appointments.begin(), appointments.end(), [&searchTitle](const Appointment& appointment) {
        return appointment.title == searchTitle;
    });

    if (it != appointments.end()) {
        // Display Appointment details
        cout << "Appointment details:\n";
        cout << "Title: " << it->title << "\n";
        cout << "Note: " << it->note << "\n";
        cout << "Date: " << it->date << "\n";
        cout << "Time: " << it->time << "\n";
        cout << "Creation Date: " << it->creationDate << "\n";
        cout << "-----------------\n";

        // Ask the user for confirmation
        char deleteChoice;
        cout << "Are you sure you want to delete this appointment? (y/n): ";
        cin >> deleteChoice;
        cin.ignore(1, '\n');
        if (tolower(deleteChoice) == 'y') {
            appointments.erase(it);
            cout << "Appointment deleted successfully!\n";
            unsavedChanges = true;
        } else {
            cout << "Deletion canceled.\n";
        }
    } else {
        cout << "Appointment not found.\n";
    }

    print_menu_tail("Appointments Menu", true); // Clear the console
}


// Function to search appointment by keywords
void AppointmentManager::searchAppointmentsByKeyword() const {
    string keyword;

    print_menu_header("Main Menu >> Appointments Menu >> Search Appointments By Keyword", true); // Clear the console

    cout << "Enter the keyword of the appointment you want to search for: ";
    
    getline(cin, keyword);

    // Remove leading and trailing spaces from the user-entered keyword
    auto keywordBegin = std::find_if(keyword.begin(), keyword.end(), [](char c) {
        return !std::isspace(c);
    });

    auto keywordEnd = std::find_if(keyword.rbegin(), keyword.rend(), [](char c) {
        return !std::isspace(c);
    }).base();

    keyword = std::string(keywordBegin, keywordEnd);

    cout << "Appointments:\n";

    for (const Appointment& appointment : appointments) {
        // Remove leading and trailing spaces from the Appointment title
        auto titleBegin = std::find_if(appointment.title.begin(), appointment.title.end(), [](char c) {
            return !std::isspace(c);
        });

        auto titleEnd = std::find_if(appointment.title.rbegin(), appointment.title.rend(), [](char c) {
            return !std::isspace(c);
        }).base();

        string trimmedTitle = std::string(titleBegin, titleEnd);

        // Compare with the user-entered keyword (ignoring case)
        if (std::search(trimmedTitle.begin(), trimmedTitle.end(), keyword.begin(), keyword.end(),
            [](char c1, char c2) { return std::toupper(c1) == std::toupper(c2); }) != trimmedTitle.end() ||
            std::search(appointment.note.begin(), appointment.note.end(), keyword.begin(), keyword.end(),
            [](char c1, char c2) { return std::toupper(c1) == std::toupper(c2); }) != appointment.note.end()) {
            // Display the Appointment details
            cout << "Title: " << appointment.title << "\n";
            cout << "Note: " << appointment.note << "\n";
            cout << "Date: " << appointment.date << "\n";
            cout << "Time: " << appointment.time << "\n";
            cout << "Creation Date: " << appointment.creationDate << "\n";
            cout << "-----------------\n";
        }
    }

    print_menu_tail("Appointments Menu", true); // Clear the console
}



void AppointmentManager::saveAppointmentsToFile() const {
    ofstream file(appointment_filename);

    for (const Appointment& appointment : appointments) {
        file << appointment.title << "\n";
        file << appointment.note << "\n";
        file << appointment.date << "\n";
        file << appointment.time << "\n";
        file << appointment.creationDate<< "\n";
    }

    file.close();
}

void AppointmentManager::loadAppointmentsFromFile() {
    ifstream file(appointment_filename);

    if (!file) {
        cout << "File not found. Starting with an empty Appointment list.\n";
        return;
    }

    Appointment appointment;
    while (getline(file, appointment.title)) {
        getline(file, appointment.note);
        getline(file, appointment.date);
        file >> appointment.time;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the newline character left in the buffer

        getline(file, appointment.creationDate);

        appointments.push_back(appointment);
    }

    file.close();
}

void AppointmentManager::runWindow_Appointment() {
    int choice;

    do {
        print_menu_header("Main Menu >> Appointments Menu", true);
        
        std::cout << "Number of Appointments: " << appointments.size() <<", "
            << "File Status: " << (unsavedChanges ? "\033[1;31mNew Changes Not Saved to the File!\033[0m" : "Up to Date") << "\n";

        std::cout << "====================\n";
        std::cout << "1. Add Appointment\n";
        std::cout << "2. View Upcoming Appointments in Daily/weekly/monthly Format\n";

        std::cout << "3. Display All Appointments\n";
        std::cout << "4. Edit an Appointment\n";
        std::cout << "5. Delete an Appointment\n";
        std::cout << "6. Search Appointments by Keyword\n";
        std::cout << "7. Sort Appointments\n";
        std::cout << "8. Save Current Changes to the File\n";
        std::cout << "9. Go Back to Main Menu\n";
        
        choice = getValidChoice(1, 9);

        switch (choice) {
            case 1:
                addAppointment();
                break;
            case 2:
                displayUpcomingAppointments();
                break;
            case 3:
                displayAppointments();
                break;
            case 4:
                editAppointment();
                break;
            case 5:
                deleteAppointment();
                break;

            case 6:
                searchAppointmentsByKeyword();
                break;
            case 7:
                listAndSortAppointments();
                break;
            case 8:
                saveAppointmentsToFile();
                std::cout << "Appointments saved. \n";
                unsavedChanges = false;
                break;
            case 9:
                std::cout << "Going to the Main Menu.\n";
                break;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 9.\n";
        }
    } while (choice != 9);
}

// Utility functions for entering Appointments details

// Utility function to enter Appointment title
string AppointmentManager::enterAppointmentTitle() const {
    std::cout << "Enter appointment title: ";
    std::string title;

    std::getline(std::cin, title);
    
    // check if the title is empty
    // check if the title is spaces only and if so ask the user to enter a valid title
    // check if the title is already used if so ask the user to enter a valid title
    // Check if the title starts with a number
    // or if it consists only of numbers
    while (
    title.empty() ||
    std::all_of(title.begin(), title.end(), [](char c) { return std::isspace(c); }) ||
    std::any_of(appointments.begin(), appointments.end(), [&title](const Appointment& appointment) { return appointment.title == title; }) ||
    std::isdigit(title.front()) ||
    std::all_of(title.begin(), title.end(), [](char c) { return std::isdigit(c); })
    ) {
        if (title.empty() || std::all_of(title.begin(), title.end(), [](char c) { return std::isspace(c); })) {
            std::cout << "Title cannot be empty or consist of spaces only. Please enter a valid title: ";
        } else if (std::any_of(appointments.begin(), appointments.end(), [&title](const Appointment& appointment) { return appointment.title == title; })) {
            std::cout << "Title already used. Please enter a different title: ";
        } else if (std::isdigit(title.front()) || std::all_of(title.begin(), title.end(), [](char c) { return std::isdigit(c); })) {
            std::cout << "Title cannot start with a number or consist only of numbers. Please enter a valid title: ";
        } else {
            // Currently, this else block covers the generic case of an invalid title.
            std::cout << "Invalid title. Please enter a valid title: ";
        }
        std::getline(std::cin, title);
    }

    return title;
}

// Utility function for addAppointment and editAppointment
string AppointmentManager::enterAppointmentNote() const {
    std::cout << "Enter appointment Note: ";
    std::string note;
    std::getline(std::cin, note);
    return note;
}


std::string AppointmentManager::enterAppointmentDate(bool accept_past) const {
    std::cout << "Enter appointment date (YYYY-MM-DD): ";
    std::string date;
    do {
        std::getline(std::cin, date);
        if (date.empty()) {
            std::cout << "Error: date cannot be empty. Please enter a valid date (YYYY-MM-DD): ";
        } else if (!isValidDateFormat(date)) {
            std::cout << "Error: Invalid date format. Please enter a valid date (YYYY-MM-DD): ";
        } else if (isPast(date) && !accept_past) {
            std::cout << "Error: Appointment Date cannot be in the past. Please enter a future date: ";
        }

    } while (date.empty() || !isValidDateFormat(date) || (isPast(date) && !accept_past) );
    return date;
}

std::string AppointmentManager::enterAppointmentTime() const {
    std::cout << "Enter appointment time (HH:MM): ";
    std::string time;
    do {
        std::getline(std::cin, time);
        if (time.empty()) {
            std::cout << "Error: time cannot be empty. Please enter a valid time (HH:MM): ";
        } else if (!isValidTimeFormat(time)) {
            std::cout << "Error: Invalid time format. Please enter a valid time (HH:MM): ";
        }
    } while (time.empty() || !isValidTimeFormat(time));
    return time;
}

// utilitis for listAndSortAppointments
void AppointmentManager::displayAppointmentsDetailed(const std::vector<Appointment>& appointments, bool clearScreen) {
    if (clearScreen) {
        // Clear the console
        std::system("clear");
    }

    // Display the sorted Appointments in a detailed format
    const int columnWidth = 20;

    std::cout << std::left << std::setw(columnWidth) << "Appointment Name";
    std::cout << std::setw(columnWidth) << "Date";
    std::cout << std::setw(columnWidth) << "Time";
    std::cout << std::setw(columnWidth) << "Creation Date\n";
    std::cout << std::string(5 * columnWidth, '-') << "\n";

    for (const Appointment& appointment : appointments) {
        // Truncate Appointment title to fit column width
        std::string truncatedTitle = appointment.title.substr(0, columnWidth - 3);
        if (appointment.title.length() > columnWidth)
            truncatedTitle += "...";

        std::cout << std::setw(columnWidth) << truncatedTitle;
        std::cout << std::setw(columnWidth) << appointment.date;
        std::cout << std::setw(columnWidth) << appointment.time;
        std::cout << std::setw(columnWidth) << appointment.creationDate << "\n";
    }
}


// utilitis for displayUpcomingAppointments
std::string AppointmentManager::enterMonth() const {
    std::cout << "Enter month (YYYY-MM): ";
    std::string month;
    do {
        std::getline(std::cin, month);
        if (month.empty()) {
            std::cout << "Error: Month cannot be empty. Please enter a valid month (YYYY-MM): ";
        } else if (!isValidMonthFormat(month)) {
            std::cout << "Error: Invalid month format. Please enter a valid month (YYYY-MM): ";
        }
    } while (month.empty() || !isValidMonthFormat(month));
    return month;
}

bool AppointmentManager::isValidMonthFormat(const std::string& month) const {
    std::tm monthDate = {};
    std::istringstream ss(month);

    // Parse the month components manually
    if (ss >> std::get_time(&monthDate, "%Y-%m")) {
        // Check if the extracted month components are valid
        return isValidDate(monthDate.tm_year + 1900, monthDate.tm_mon + 1, 1);
    }

    return false; // Invalid month format, handled separately
}


void AppointmentManager::displayAppointmentsDaily(const std::string& date) const {
    // Filter appointments for the specified date
    std::vector<Appointment> dailyAppointments;
    std::copy_if(appointments.begin(), appointments.end(), std::back_inserter(dailyAppointments),
                 [&date](const Appointment& app) { return app.date == date; });

    // Display the appointments for the day
    displayUpcomingAppointmentsDetailed(dailyAppointments, "daily");
}

void AppointmentManager::displayAppointmentsWeekly(const std::string& startDate) const {
    // Assuming a week has 7 days for simplicity
    const int daysInWeek = 7;

    // Convert the start date to a time point
    std::tm tmDate = convertStringToTm(startDate, "%Y-%m-%d");
    std::chrono::system_clock::time_point startDateTime = std::chrono::system_clock::from_time_t(std::mktime(&tmDate));

    // Calculate the end date as one week from the start date
    std::chrono::system_clock::time_point endDateTime = startDateTime + std::chrono::hours(daysInWeek * 24);

    // Filter appointments for the specified week
    std::vector<Appointment> weeklyAppointments;
    std::copy_if(appointments.begin(), appointments.end(), std::back_inserter(weeklyAppointments),
                 [&startDateTime, &endDateTime](const Appointment& app) {
                     std::chrono::system_clock::time_point appDateTime =
                         convertStringToTimePoint(app.date + " " + app.time, "%Y-%m-%d %H:%M");
                     return appDateTime >= startDateTime && appDateTime < endDateTime;
                 });

    // Display the appointments for the week
    displayUpcomingAppointmentsDetailed(weeklyAppointments, "weekly");
}

void AppointmentManager::displayAppointmentsMonthly(const std::string& month) const {
    // Filter appointments for the specified month
    std::vector<Appointment> monthlyAppointments;
    std::copy_if(appointments.begin(), appointments.end(), std::back_inserter(monthlyAppointments),
                 [&month](const Appointment& app) { return app.date.substr(0, 7) == month; });

    // Display the appointments for the month
    displayUpcomingAppointmentsDetailed(monthlyAppointments, "monthly");
}

// displayUpcomingAppointmentsDetailed in this style
// Daily Appointments - Date: 2023-12-15
// Weekly Appointments - Week of 2023-12-11 to 2023-12-17
// Monthly Appointments - December 2023

// 1. Meeting with Client - 10:00 AM
//    Notes: Discuss project updates and deliverables.

// 2. Lunch with Colleague - 12:30 PM
//    Notes: Informal catch-up and team bonding.

// etc.

void AppointmentManager::displayUpcomingAppointmentsDetailed(const std::vector<Appointment>& appointments, const std::string& type) const {
    // Check if there are any appointments
    if (appointments.empty()) {
        std::cout << "No upcoming appointments.\n";
        return;
    }

    
    // Display header based on the type (daily, weekly, monthly)
    std::string header;
    if (type == "daily") {
        header = "Daily Appointments - Date: " + appointments[0].date;
    } else if (type == "weekly") {
        header = "Weekly Appointments - Week from " + appointments[0].date + " to " + appointments.back().date;
    } else if (type == "monthly") {
        header = "Monthly Appointments - " + appointments[0].date.substr(0, 7);
    }

    std::cout << "---------------------------------------------\n";
    std::cout << header << "\n\n";
    std::cout << "---------------------------------------------\n";
    // Display each appointment
    for (size_t i = 0; i < appointments.size(); ++i) {
        const Appointment& app = appointments[i];

        // Display day for weekly appointments
        std::string dayOfWeek = getDayOfWeek(app.date);
        std::cout << dayOfWeek << ":\n";

        // Display each appointment's details
        std::cout << i + 1 << ". " << app.title << " - " << app.time << "\n";
        std::cout << "   Date: " << app.date << "\n";
        std::cout << "   Notes: " << app.note << "\n\n";
        
    }
}


// function sortAppointmentsByDate
std::vector<Appointment> AppointmentManager::sortAppointmentsByDate(const std::vector<Appointment>& appointments) {
    // Make a copy of the original appointments vector
    std::vector<Appointment> sortedAppointments = appointments;

    // Sort the appointments by date
    std::sort(sortedAppointments.begin(), sortedAppointments.end(), [](const Appointment& a, const Appointment& b) {
        // Convert the date and time strings to time points
        std::chrono::system_clock::time_point dateTimeA = convertStringToTimePoint(a.date + " " + a.time, "%Y-%m-%d %H:%M");
        std::chrono::system_clock::time_point dateTimeB = convertStringToTimePoint(b.date + " " + b.time, "%Y-%m-%d %H:%M");

        // Compare the time points
        return dateTimeA < dateTimeB;
    });

    return sortedAppointments;
}
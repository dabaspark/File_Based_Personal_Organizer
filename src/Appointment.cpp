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

    // Display information about the add task process
    std::cout << "Add appointment:\n";
    std::cout << "Please enter the details for the new appointment.\n";
    std::cout << "You will be prompted for the title, note, date, and time.\n";
    std::cout << "You can choose to mark the task as completed later.\n";


    Appointment newAppointment;

    newAppointment.title = enterAppointmentTitle();
    newAppointment.note = enterAppointmentNote();
    newAppointment.date = enterAppointmentDate();
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

void AppointmentManager::listAndSortAppointments() {
    int sortOption;

    print_menu_header("Main Menu >> Appointments Menu >> List and Sort Appointments", true); // Clear the console

    // Display sorting options
    std::cout << "Sort tasks by:\n";
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
            std::sort(appointments.begin(), appointments.end(), [](const Appointment& a, const Appointment& b) {
                return a.date < b.date;
            });
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
                editedAppointment.date = enterAppointmentDate();
                break;
            case 4:
                editedAppointment.time = enterAppointmentTime();
                break;
            case 5:
                // If the user chooses to edit all fields, update all fields
                editedAppointment.title = enterAppointmentTitle();
                editedAppointment.note = enterAppointmentNote();
                editedAppointment.date = enterAppointmentDate();
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

    displayTasksDetailed(tasks, false);
    std::cout << "---------------------------------------------\n";
    cout << "Enter the title of the task you want to delete: ";

    //cin.ignore(); // Ignore the newline character left in the buffer
    
    getline(cin, searchTitle);

    auto it = find_if(tasks.begin(), tasks.end(), [&searchTitle](const Task& task) {
        return task.title == searchTitle;
    });

    if (it != tasks.end()) {
        // Display task details
        cout << "Task details:\n";
        cout << "Title: " << it->title << "\n";
        cout << "Description: " << it->description << "\n";
        cout << "Deadline: " << it->deadline << "\n";
        cout << "Priority: " << it->priority << "\n";
        cout << "Status: " << (it->completed ? "Completed" : "Incomplete") << "\n";
        cout << "Creation Date: " << it->creationDate << "\n";
        cout << "-----------------\n";

        // Ask the user for confirmation
        char deleteChoice;
        cout << "Are you sure you want to delete this task? (y/n): ";
        cin >> deleteChoice;
        cin.ignore(1, '\n');
        if (tolower(deleteChoice) == 'y') {
            tasks.erase(it);
            cout << "Task deleted successfully!\n";
            unsavedChanges = true;
        } else {
            cout << "Deletion canceled.\n";
        }
    } else {
        cout << "Task not found.\n";
    }

    // press any key to go back to main menu
    std::cout << "Press any key to go back to main menu...\n";
    std::cin.get();
    // Clear the console
    std::system("clear");
}


void AppointmentManager::markTaskCompleted() {
    string searchTitle;

    // Clear the console
    std::system("clear");

    // Display the Heading of the menu
    std::cout << "====================\n";
    std::cout << "Main Menu >> Mark Task Completed:\n";
    std::cout << "====================\n";

    // Display information about the add task process
    std::cout << "You will be prompted for the title of the task to mark completed\n";
    std::cout << "---------------------------------------------\n";
    std::cout << "The List of The tasks are:\n";
    std::cout << "---------------------------------------------\n";
    displayTasksDetailed(tasks, false);

    std::cout << "---------------------------------------------\n";
    cout << "Enter the title of the task you want to mark as completed: ";
    //cin.ignore(); // Ignore the newline character left in the buffer
    getline(cin, searchTitle);

    auto it = find_if(tasks.begin(), tasks.end(), [&searchTitle](const Task& task) {
        return task.title == searchTitle;
    });

    if (it != tasks.end()) {
        if (it->completed) {
            cout << "Task is already marked as completed.\n";
        } else {
            it->completed = true;
            cout << "Task marked as completed!\n";
            unsavedChanges = true;
        }
    } else {
        cout << "Task not found.\n";
    }

    // press any key to go back to main menu
    std::cout << "Press any key to go back to main menu...\n";
    std::cin.get();
    // Clear the console
    std::system("clear");
}


// Function to search tasks by keywords
void AppointmentManager::searchTasksByKeyword() const {
    string keyword;

    // Clear the console
    std::system("clear");
    // Display the Heading of the menu
    std::cout << "====================\n";
    std::cout << "Main Menu >> Search Tasks By Keyword:\n";
    std::cout << "====================\n";

    cout << "Enter the keyword of the task you want to search for: ";
    //cin.ignore(); // Ignore the newline character left in the buffer
    getline(cin, keyword);

    // Remove leading and trailing spaces from the user-entered keyword
    auto keywordBegin = std::find_if(keyword.begin(), keyword.end(), [](char c) {
        return !std::isspace(c);
    });

    auto keywordEnd = std::find_if(keyword.rbegin(), keyword.rend(), [](char c) {
        return !std::isspace(c);
    }).base();

    keyword = std::string(keywordBegin, keywordEnd);

    cout << "Tasks:\n";

    for (const Task& task : tasks) {
        // Remove leading and trailing spaces from the task title
        auto titleBegin = std::find_if(task.title.begin(), task.title.end(), [](char c) {
            return !std::isspace(c);
        });

        auto titleEnd = std::find_if(task.title.rbegin(), task.title.rend(), [](char c) {
            return !std::isspace(c);
        }).base();

        string trimmedTitle = std::string(titleBegin, titleEnd);

        // Compare with the user-entered keyword (ignoring case)
        if (std::search(trimmedTitle.begin(), trimmedTitle.end(), keyword.begin(), keyword.end(),
            [](char c1, char c2) { return std::toupper(c1) == std::toupper(c2); }) != trimmedTitle.end() ||
            std::search(task.description.begin(), task.description.end(), keyword.begin(), keyword.end(),
            [](char c1, char c2) { return std::toupper(c1) == std::toupper(c2); }) != task.description.end()) {
            // Display the task details
            cout << "Title: " << task.title << "\n";
            cout << "Description: " << task.description << "\n";
            cout << "Deadline: " << task.deadline << "\n";
            cout << "Priority: " << task.priority << "\n";
            cout << "Status: " << (task.completed ? "Completed" : "Incomplete") << "\n";
            cout << "Creation Date: " << task.creationDate << "\n";
            cout << "-----------------\n";
        }
    }

    // press any key to go back to main menu
    std::cout << "Press any key to go back to main menu...\n";
    std::cin.get();
    // Clear the console
    std::system("clear");
}



void AppointmentManager::saveTasksToFile() const {
    ofstream file(task_filename);

    for (const Task& task : tasks) {
        file << task.title << "\n";
        file << task.description << "\n";
        file << task.deadline << "\n";
        file << task.priority << "\n";
        file << task.completed << "\n";
        file << task.creationDate<< "\n";
    }

    file.close();
}

void AppointmentManager::loadTasksFromFile() {
    ifstream file(task_filename);

    if (!file) {
        cout << "File not found. Starting with an empty task list.\n";
        return;
    }

    Task task;
    while (getline(file, task.title)) {
        getline(file, task.description);
        getline(file, task.deadline);
        file >> task.priority;
        file >> task.completed;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the newline character left in the buffer

        getline(file, task.creationDate);

        tasks.push_back(task);
    }

    file.close();
}

void AppointmentManager::runWindow_Task() {
    int choice;

    do {
        // Clear the console
        std::system("clear");
        // Display the menu
        std::cout << "====================\n";
        std::cout << "Main Menu\n";
        std::cout << "====================\n";
        std::cout << "Number of tasks: " << tasks.size() <<", "
            << "Completed tasks: " << std::count_if(tasks.begin(), tasks.end(), [](const Task& task) {
                return task.completed;
            }) << ", " << "Incomplete tasks: " << std::count_if(tasks.begin(), tasks.end(), [](const Task& task) {
                return !task.completed;
            })<< ", " << "File Status: " << (unsavedChanges ? "\033[1;31mNew changes not saved to the file!\033[0m" : "Up to Date") << "\n";

        std::cout << "====================\n";
        std::cout << "Menu:\n";
        std::cout << "1. Add Task\n";
        std::cout << "2. Display Tasks\n";
        std::cout << "3. Edit Task\n";
        std::cout << "4. Delete Task\n";
        std::cout << "5. Mark Task as Completed\n";
        std::cout << "6. Search Tasks by Keyword\n";
        std::cout << "7. Sort Tasks\n";
        std::cout << "8. Save Current Changes to File\n";
        std::cout << "9. Save and Quit\n";
        std::cout << "10. Quit without Saving\n";
        

        //std::cout << "Enter your choice (1-10): ";
        choice = getValidChoice(1, 10);

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                displayTasks();
                break;
            case 3:
                editTask();
                break;
            case 4:
                deleteTask();
                break;
            case 5:
                markTaskCompleted();
                break;
            case 6:
                searchTasksByKeyword();
                break;
            case 7:
                listAndSortTasks();
                break;
            case 8:
                saveTasksToFile();
                std::cout << "Tasks saved. \n";
                unsavedChanges = false;
                break;
            case 9:
                saveTasksToFile();
                std::cout << "Tasks saved. Exiting program.\n";
                break;
            case 10:
                if (unsavedChanges) {
                    char exitChoice;
                    std::cout << "Are you sure you want to exit without saving? (y/n): ";
                    std::cin >> exitChoice;
                    cin.ignore(1, '\n');
                    if (tolower(exitChoice) == 'y') {
                        std::cout << "Exiting program without saving.\n";
                        return;
                    } else {
                        choice = 0; // Reset the choice to display the menu again
                        std::cout << "Continuing the program.\n";
                    }
                } else {
                    std::cout << "Exiting program.\n";
                }
                break;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 10.\n";
        }
    } while (choice != 9 && choice != 10);
}

// Utility functions for entering task details

// Utility function to enter task title
string AppointmentManager::enterTaskTitle() const {
    std::cout << "Enter task title: ";
    std::string title;
    //std::cin.ignore();
    std::getline(std::cin, title);
    
    // check if the title is empty
    // check if the title is spaces only and if so ask the user to enter a valid title
    // check if the title is already used if so ask the user to enter a valid title
    // Check if the title starts with a number
    // or if it consists only of numbers
    while (
    title.empty() ||
    std::all_of(title.begin(), title.end(), [](char c) { return std::isspace(c); }) ||
    std::any_of(tasks.begin(), tasks.end(), [&title](const Task& task) { return task.title == title; }) ||
    std::isdigit(title.front()) ||
    std::all_of(title.begin(), title.end(), [](char c) { return std::isdigit(c); })
    ) {
        if (title.empty() || std::all_of(title.begin(), title.end(), [](char c) { return std::isspace(c); })) {
            std::cout << "Title cannot be empty or consist of spaces only. Please enter a valid title: ";
        } else if (std::any_of(tasks.begin(), tasks.end(), [&title](const Task& task) { return task.title == title; })) {
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

// Utility function for addTask and editTask
string AppointmentManager::enterTaskDescription() const {
    std::cout << "Enter task description: ";
    std::string description;
    std::getline(std::cin, description);
    return description;
}


std::string AppointmentManager::enterTaskDeadline() const {
    std::cout << "Enter task deadline (YYYY-MM-DD): ";
    std::string deadline;
    do {
        std::getline(std::cin, deadline);
        if (deadline.empty()) {
            std::cout << "Error: Deadline cannot be empty. Please enter a valid deadline (YYYY-MM-DD): ";
        } else if (!isValidDateFormat(deadline)) {
            std::cout << "Error: Invalid date format. Please enter a valid deadline (YYYY-MM-DD): ";
        } else if (isPast(deadline)) {
            std::cout << "Error: Deadline cannot be in the past. Please enter a future deadline: ";
        }
    } while (deadline.empty() || !isValidDateFormat(deadline) || isPast(deadline));
    return deadline;
}

// enter task priority

int AppointmentManager::enterTaskPriority() const {
    int priority;
    bool isValidInput;

    do {
        isValidInput = true; // Assume input is valid unless proven otherwise

        std::cout << "Enter task priority (1-5): ";

        std::string input;
        std::getline(std::cin, input);

        // Check if the input is empty
        if (input.empty()) {
            std::cout << "Invalid input. Please enter a value.\n";
            isValidInput = false;
            continue;  // Skip the rest of the loop for empty input
        }

        // Check if the input consists only of digits
        if (!std::all_of(input.begin(), input.end(), ::isdigit)) {
            std::cout << "Invalid input. Please enter a valid integer.\n";
            isValidInput = false;
            continue;  // Skip the rest of the loop for non-numeric input
        }

        try {
            size_t pos;
            priority = std::stoi(input, &pos);

            // Check if the entire input was converted to an integer
            if (pos < input.size()) {
                throw std::invalid_argument("Invalid input. Please enter an integer.");
            }

            // Check if the input is within the valid range
            if (priority < 1 || priority > 5) {
                std::cout << "Invalid input. Priority must be between 1 and 5.\n";
                isValidInput = false;
            }

        } catch (const std::invalid_argument& e) {
            std::cout << e.what() << "\n";
            isValidInput = false;
        } catch (const std::out_of_range& e) {
            std::cout << "Invalid input. Entered value is out of range for integer.\n";
            isValidInput = false;
        }

    } while (!isValidInput);

    return priority;
}

// utilitis for edittask
// Function to trim whitespaces from both ends of a string
std::string AppointmentManager::trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");
    return (start != std::string::npos && end != std::string::npos) ? str.substr(start, end - start + 1) : "";
}


// utilitis for listAndSortTasks
void AppointmentManager::displayTasksDetailed(const std::vector<Task>& tasks, bool clearScreen) {
    if (clearScreen) {
        // Clear the console
        std::system("clear");
    }

    // Display the sorted tasks in a detailed format
    const int columnWidth = 20;

    std::cout << std::left << std::setw(columnWidth) << "Task Name";
    std::cout << std::setw(columnWidth) << "Deadline";
    std::cout << std::setw(columnWidth) << "Priority";
    std::cout << std::setw(columnWidth) << "Completed";
    std::cout << std::setw(columnWidth) << "Creation Date\n";
    std::cout << std::string(5 * columnWidth, '-') << "\n";

    for (const Task& task : tasks) {
        // Truncate task title to fit column width
        std::string truncatedTitle = task.title.substr(0, columnWidth - 3);
        if (task.title.length() > columnWidth)
            truncatedTitle += "...";

        std::cout << std::setw(columnWidth) << truncatedTitle;
        std::cout << std::setw(columnWidth) << task.deadline;
        std::cout << std::setw(columnWidth) << task.priority;
        std::cout << std::setw(columnWidth) << (task.completed ? "Yes" : "No");
        std::cout << std::setw(columnWidth) << task.creationDate << "\n";
    }
}

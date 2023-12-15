// Task.cpp

#include "include/Task.h"


// Constructor
TaskManager::TaskManager(const std::string& filename) : task_filename(filename) {
    loadTasksFromFile();
    unsavedChanges = false;
}

// Destructor
TaskManager::~TaskManager() {
    //saveTasksToFile();
}

void TaskManager::addTask() {
    Task newTask;

    newTask.title = enterTaskTitle();
    newTask.description = enterTaskDescription();
    newTask.deadline = enterTaskDeadline();
    newTask.priority = enterTaskPriority();
    newTask.completed = false;

    auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    newTask.creationDate = ctime(&now); // Convert to string
    newTask.creationDate.pop_back(); // Remove the newline character

    // ask the user if they are sure they want to add the task
    char choice;
    cout << "Are you sure you want to add this task? (y/n): ";
    cin >> choice;
    if (tolower(choice) != 'y' && tolower(choice) != 'Y') {
        cout << "Task not added.\n";
        return;
    }
    tasks.push_back(newTask);
    unsavedChanges = true;
    std::cout << "Task added successfully!\n";
}

void TaskManager::displayTasks() const {
    std::cout << "Tasks:\n";

    for (const Task& task : tasks) {
        std::cout << "Title: " << task.title << "\n";
        std::cout << "Description: " << task.description << "\n";
        std::cout << "Deadline: " << task.deadline << "\n";
        std::cout << "Priority: " << task.priority << "\n";
        std::cout << "Status: " << (task.completed ? "Completed" : "Incomplete") << "\n";
        std::cout << "Creation Date: " << task.creationDate << "\n";
        std::cout << "-----------------\n";
    }
}

void TaskManager::listAndSortTasks() {
    int sortOption;

    // Display sorting options
    std::cout << "Sort tasks by:\n";
    std::cout << "1. Title\n";
    std::cout << "2. Deadline\n";
    std::cout << "3. Creation Date\n";
    std::cout << "4. Priority\n";
    //std::cout << "Enter your choice (1-4): ";

    // get the user input
    sortOption = getValidChoice(1, 4);

    // Make a copy of the original tasks vector
    std::vector<Task> originalTasks = tasks;

    // Perform sorting based on user choice
    switch (sortOption) {
        case 1:
            std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
                // Perform case-insensitive comparison
                return std::lexicographical_compare(
                    a.title.begin(), a.title.end(),
                    b.title.begin(), b.title.end(),
                    [](char c1, char c2) { return std::tolower(c1) < std::tolower(c2); }
                );
            });
            break;
        case 2:
            std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
                return a.deadline < b.deadline;
            });
            break;
        case 3:
            std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
                return a.creationDate < b.creationDate;
            });
            break;
        case 4:
            std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
                return a.priority < b.priority;
            });
            break;
    }

    // Display the sorted tasks
    displayTasks();

    // Ask the user for confirmation
    char choice;
    std::cout << "Are you sure you want to change the order of the tasks? (y/n): ";
    std::cin >> choice;
    if (tolower(choice) != 'y' && tolower(choice) != 'Y') {
        // Revert to the original order
        tasks = originalTasks;
        std::cout << "Order is not changed.\n";
        return;
    }

    std::cout << "Task order changed!\n";
    unsavedChanges = true;
}




void TaskManager::editTask() {
    string searchTitle;
    cout << "Enter the title of the task you want to edit: ";
    cin.ignore(); // Ignore the newline character left in the buffer
    getline(cin, searchTitle);

    auto it = find_if(tasks.begin(), tasks.end(), [&searchTitle](const Task& task) {
        return task.title == searchTitle;
    });

    if (it != tasks.end()) {
        Task editedTask = *it;  // Create a copy of the original task

        // Display editing options
        cout << "Edit task:\n";
        cout << "1. Title\n";
        cout << "2. Description\n";
        cout << "3. Deadline\n";
        cout << "4. Priority\n";
        cout << "5. All\n";
        cout << "Enter your choice (1-5): ";

        int editOption;
        cin >> editOption;

        // Validate user input
        while (editOption < 1 || editOption > 5) {
            cout << "Invalid choice. Please enter a number between 1 and 5.\n";
            cin >> editOption;
        }
        cin.ignore(); // Ignore the newline character left in the buffer

        // Perform editing based on user choice
        switch (editOption) {
            case 1:
                editedTask.title = enterTaskTitle();
                break;
            case 2:
                editedTask.description = enterTaskDescription();
                break;
            case 3:
                editedTask.deadline = enterTaskDeadline();
                break;
            case 4:
                editedTask.priority = enterTaskPriority();
                break;
            case 5:
                // If the user chooses to edit all fields, update all fields
                editedTask.title = enterTaskTitle();
                editedTask.description = enterTaskDescription();
                editedTask.deadline = enterTaskDeadline();
                editedTask.priority = enterTaskPriority();
                break;
        }

        // Ask the user if they want to save changes
        char saveChoice;
        cout << "Are you sure you want to save the changes? (y/n): ";
        cin >> saveChoice;

        if (tolower(saveChoice) == 'y') {
            // If the user chooses to save, update the original task
            *it = editedTask;
            //saveTasksToFile();  // Save changes immediately
            cout << "Changes saved!\n";
            unsavedChanges = true;
        } else {
            // If the user chooses not to save, discard the changes
            cout << "Changes discarded.\n";
        }
    } else {
        cout << "Task not found.\n";
    }
}



void TaskManager::deleteTask() {
    string searchTitle;
    cout << "Enter the title of the task you want to delete: ";

    cin.ignore(); // Ignore the newline character left in the buffer
    
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
}


void TaskManager::markTaskCompleted() {
    string searchTitle;
    cout << "Enter the title of the task you want to mark as completed: ";
    cin.ignore(); // Ignore the newline character left in the buffer
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
}


// Function to search tasks by keywords
void TaskManager::searchTasksByKeyword() const {
    string keyword;
    cout << "Enter the keyword you want to search for: ";
    cin.ignore(); // Ignore the newline character left in the buffer
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
}



void TaskManager::saveTasksToFile() const {
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

void TaskManager::loadTasksFromFile() {
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
        file.ignore(); // Ignore the newline character left in the buffer

        getline(file, task.creationDate);

        tasks.push_back(task);
    }

    file.close();
}

void TaskManager::runWindow() {
    int choice;

    do {
        std::cout << "Number of tasks: " << tasks.size() <<", "
            << "Completed tasks: " << std::count_if(tasks.begin(), tasks.end(), [](const Task& task) {
                return task.completed;
            }) << ", " << "Incomplete tasks: " << std::count_if(tasks.begin(), tasks.end(), [](const Task& task) {
                return !task.completed;
            })<< ", " << "File Status: " << (unsavedChanges ? "New changes not saved to the file" : "Up to Date") << "\n";

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

// Function to validate and get user input as an integer within a specified range
int TaskManager::getValidChoice(int min, int max) {
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

// Utility functions for entering task details

// Utility function to enter task title
string TaskManager::enterTaskTitle() const {
    std::cout << "Enter task title: ";
    std::string title;
    std::cin.ignore();
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
string TaskManager::enterTaskDescription() const {
    std::cout << "Enter task description: ";
    std::string description;
    std::getline(std::cin, description);
    return description;
}


std::string TaskManager::enterTaskDeadline() const {
    std::cout << "Enter task deadline (YYYY-MM-DD): ";
    std::string deadline;
    do {
        std::getline(std::cin, deadline);
        if (deadline.empty()) {
            std::cout << "Error: Deadline cannot be empty. Please enter a valid deadline (YYYY-MM-DD): ";
        } else if (!isValidDateFormat(deadline)) {
            std::cout << "Error: Invalid date format. Please enter a valid deadline (YYYY-MM-DD): ";
        } else if (isPastDeadline(deadline)) {
            std::cout << "Error: Deadline cannot be in the past. Please enter a future deadline: ";
        }
    } while (deadline.empty() || !isValidDateFormat(deadline) || isPastDeadline(deadline));
    return deadline;
}

// enter task priority

int TaskManager::enterTaskPriority() const {
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

// utlitity function to enterTaskDeadline function

// Utility function to check if the date has a valid format (YYYY-MM-DD)
bool TaskManager::isValidDateFormat(const std::string& date) const {
    std::tm testDate = {};
    std::istringstream ss(date);

    // Parse the date components manually
    ss >> std::get_time(&testDate, "%Y-%m-%d");

    // Check if the entire input string is consumed and date components are valid
    return !ss.fail() && ss.eof() && isValidDate(testDate.tm_year + 1900, testDate.tm_mon + 1, testDate.tm_mday);
}

// Utility function to check if the deadline is in the past
bool TaskManager::isPastDeadline(const std::string& deadline) const {
    std::tm deadlineDate = {};
    std::istringstream ss(deadline);

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
bool TaskManager::isValidDate(int year, int month, int day) const {
    // Some basic validation
    return (year >= 1900 && month >= 1 && month <= 12 && day >= 1 && day <= 31);
}
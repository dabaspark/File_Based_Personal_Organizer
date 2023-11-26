// Task.cpp

#include "include/Task.h"


// Constructor
TaskManager::TaskManager(const std::string& filename) : task_filename(filename) {
    loadTasksFromFile();
}

// Destructor
TaskManager::~TaskManager() {
    //saveTasksToFile();
}

void TaskManager::addTask() {
    Task newTask;

    std::cout << "Enter task title: ";
    std::cin.ignore(); // Clear the newline character from the buffer
    std::getline(std::cin, newTask.title);

    std::cout << "Enter task description: ";
    std::getline(std::cin, newTask.description);

    std::cout << "Enter task deadline: ";
    std::getline(std::cin, newTask.deadline);

    std::cout << "Enter task priority (1-5): ";
    std::cin >> newTask.priority;

    newTask.completed = false;

    // Get the current date
    auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    newTask.creationDate = ctime(&now); // Convert to string
    newTask.creationDate.pop_back();

    // ask the user if they are sure they want to add the task
    char choice;
    cout << "Are you sure you want to add this task? (y/n): ";
    cin >> choice;
    if (tolower(choice) != 'y' && tolower(choice) != 'Y') {
        cout << "Task not added.\n";
        return;
    }
    tasks.push_back(newTask);

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

        cout << "Enter new task title: ";
        getline(cin, editedTask.title);

        cout << "Enter new task description: ";
        getline(cin, editedTask.description);

        cout << "Enter new task deadline: ";
        getline(cin, editedTask.deadline);

        cout << "Enter new task priority (1-5): ";
        cin >> editedTask.priority;

        // Ask the user if they want to save changes
        char saveChoice;
        cout << "Are you sure you want to save the changes? (y/n): ";
        cin >> saveChoice;

        if (tolower(saveChoice) == 'y') {
            // If user chooses to save, update the original task
            *it = editedTask;
            //saveTasksToFile();  // Save changes immediately
            cout << "Changes saved!\n";
        } else {
            // If user chooses not to save, discard the changes
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
        it->completed = true;
        cout << "Task marked as completed!\n";
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
        std::cout << "Menu:\n";
        std::cout << "1. Add Task\n";
        std::cout << "2. Display Tasks\n";
        std::cout << "3. Edit Task\n";
        std::cout << "4. Delete Task\n";
        std::cout << "5. Mark Task as Completed\n";
        std::cout << "6. Search Tasks by Keyword\n";
        std::cout << "7. Save Current Changes to File\n";
        std::cout << "8. Save and Quit\n";
        std::cout << "9. Quit without Saving\n";
        std::cout << "Enter your choice (1-9): ";
        std::cin >> choice;

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
                saveTasksToFile();
                std::cout << "Tasks saved. \n";
                break;
            case 8:
                saveTasksToFile();
                std::cout << "Tasks saved. Exiting program.\n";
                break;
            case 9:
                std::cout << "Exiting program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 6.\n";
        }
    } while (choice != 8 && choice != 9);
}

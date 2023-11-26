// Task.cpp

#include "include/Task.h"


// Constructor
TaskManager::TaskManager(const std::string& filename) : task_filename(filename) {
    loadTasksFromFile();
}

// Destructor
TaskManager::~TaskManager() {
    saveTasksToFile();
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
        cout << "Enter new task title: ";
        getline(cin, it->title);

        cout << "Enter new task description: ";
        getline(cin, it->description);

        cout << "Enter new task deadline: ";
        getline(cin, it->deadline);

        cout << "Enter new task priority (1-5): ";
        cin >> it->priority;

        cout << "Task edited successfully!\n";
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
        tasks.erase(it);
        cout << "Task deleted successfully!\n";
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
        std::cout << "6. Save and Quit\n";
        std::cout << "Enter your choice (1-6): ";
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
                saveTasksToFile();
                std::cout << "Tasks saved. Exiting program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 6.\n";
        }
    } while (choice != 6);
}

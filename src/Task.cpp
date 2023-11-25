// Task.cpp
#include "include/Task.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>

TaskManager::TaskManager() : head(nullptr) {
    loadFromFile(); // Load data from files when the program starts
}

TaskManager::~TaskManager() {
    saveToFile(); // Save data to files when the program exits
}

void TaskManager::runMenu() {
    int choice;

    do {
        std::cout << "===== Task Manager Menu =====" << std::endl;
        std::cout << "1. Add Task\n2. List Tasks\n3. Delete Task\n4. Edit Task\n5. Mark Task as Completed\n6. Search Tasks\n0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string title, description, deadline;
                int priority;

                std::cout << "Enter task details:\n";
                std::cout << "Title: ";
                std::cin.ignore(); // Consume the newline character left by previous input
                std::getline(std::cin, title);
                std::cout << "Description: ";
                std::getline(std::cin, description);
                std::cout << "Deadline: ";
                std::getline(std::cin, deadline);
                std::cout << "Priority (1-5): ";
                std::cin >> priority;

                addTask(title, description, deadline, priority);
                break;
            }
            case 2:
                listTasks();
                break;
            case 3: {
                std::string title;
                std::cout << "Enter the title of the task to delete: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                deleteTask(title);
                break;
            }
            case 4: {
                std::string title;
                std::cout << "Enter the title of the task to edit: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                editTask(title);
                break;
            }
            case 5: {
                std::string title;
                std::cout << "Enter the title of the task to mark as completed: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                markTaskCompleted(title);
                break;
            }
            case 6: {
                std::string keyword;
                std::cout << "Enter keyword to search tasks: ";
                std::cin.ignore();
                std::getline(std::cin, keyword);
                searchTasks(keyword);
                break;
            }
            case 0:
                std::cout << "Exiting Task Manager. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);
}

void TaskManager::loadFromFile() {
    std::ifstream file("tasks.txt"); // Assuming the file is named "tasks.txt"

    if (!file.is_open()) {
        std::cout << "No previous data found.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        TaskNode* newNode = new TaskNode;

        // Read task details from the file
        iss >> newNode->title >> newNode->description >> newNode->deadline >> newNode->priority >> newNode->completed >> newNode->creationDate;

        newNode->next = nullptr;
        insertTaskNode(newNode);
    }

    file.close();
}

void TaskManager::saveToFile() {
    std::ofstream file("tasks.txt"); // Assuming the file is named "tasks.txt"

    if (!file.is_open()) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }

    TaskNode* current = head;
    while (current != nullptr) {
        file << current->title << ' ' << current->description << ' ' << current->deadline << ' '
             << current->priority << ' ' << current->completed << ' ' << current->creationDate << '\n';
        current = current->next;
    }

    file.close();
}
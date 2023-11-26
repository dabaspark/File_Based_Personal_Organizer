/// Task.h
#ifndef TASK_H
#define TASK_H
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>  // for date and time operations
#include <cctype>  //for task keywork search // for character classification functions

using namespace std;

// Define the structure for a task
struct Task {
    string title;       // Title of the task
    string description; // Description of the task
    string deadline;    // Deadline of the task
    string creationDate; // Creation date of the task
    int priority;       // Priority of the task
    bool completed;     // Status of the task
};

class TaskManager {
public:
    // Constructor
    TaskManager(const std::string& filename);

    // Destructor
    ~TaskManager();

    // Function to add a new task
    void addTask();

    // Function to display all tasks
    void displayTasks() const;

    // Function to edit a task
    void editTask();

    // Function to delete a task
    void deleteTask();

    // Function to mark a task as completed
    void markTaskCompleted();

    // Function to search for a task
    void searchTasksByKeyword() const;

    // Function to save tasks to a file
    void saveTasksToFile() const;

    // Function to load tasks from a file
    void loadTasksFromFile() ;

    // Function to run the task management window
    void runWindow();

private:
    std::vector<Task> tasks;
    std::string task_filename;
};

#endif // TASK_H
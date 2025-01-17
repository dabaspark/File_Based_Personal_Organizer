/// Task.h
#ifndef TASK_H
#define TASK_H
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>  // for date and time operations
#include <cctype>  //for task keywork search // for character classification functions
#include <sstream> // for string stream operations
#include <ctime>    // for time operations
#include <iomanip>  // for date and time formatting
#include <limits>  // for limiting user input in display menu (error handling)
#include <thread> // for std::this_thread::sleep_for
#include <chrono> // for std::chrono::seconds

#include "Utilities.h"

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
    bool unsavedChanges;
    std::vector<Task> tasks;

    // Constructor
    TaskManager(const std::string& filename);

    // Destructor
    ~TaskManager();

    // Function to add a new task
    void addTask();

    // Function to display all tasks
    void displayTasks();

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
    void runWindow_Task();

    // Function to sort tasks
    void listAndSortTasks();

    // Function to export to CSV
    void exportTasksToCSV(const std::string& filename) const;

private:
    std::string task_filename;

    // Utility functions for entering task details
    string enterTaskTitle() const;
    string enterTaskDescription() const;
    string enterTaskDeadline() const;
    int enterTaskPriority() const;

    // utilitis for listAndSortTasks
    void displayTasksDetailed(const std::vector<Task>& tasks, bool clearScreen);
    std::vector<Task> sortTasksByDate(const std::vector<Task>& tasks);
};

#endif // TASK_H
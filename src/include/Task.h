// Task.h
#ifndef TASK_H
#define TASK_H
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Define the structure for a task
struct Task {
    string title;       // Title of the task
    string description; // Description of the task
    string deadline;    // Deadline of the task
    int priority;       // Priority of the task
    bool completed;     // Status of the task
};

// Function to add a new task
void addTask(vector<Task>& tasks);

// Function to display all tasks
void displayTasks(const vector<Task>& tasks);

// Function to edit a task
void editTask(vector<Task>& tasks);

// Function to delete a task
void deleteTask(vector<Task>& tasks);

// Function to mark a task as completed
void markTaskCompleted(vector<Task>& tasks);

// Function to load tasks from a file
void loadTasksFromFile(vector<Task>& tasks, const string& filename);

// Function to save tasks to a file
void saveTasksToFile(const vector<Task>& tasks, const string& filename);

// Function to show the task menu
void task_runwindow(vector<Task>& tasks, const string& filename);

#endif // TASK_H

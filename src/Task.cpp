// Task.cpp

#include "include/Task.h"

// Function to add a new task
void addTask(vector<Task>& tasks) {
    Task newTask;   // Create a new empty-valued task
    
    cout << "Enter task title: ";   
    getline(cin, newTask.title);
    
    cout << "Enter task description: ";
    getline(cin, newTask.description);
    
    cout << "Enter task deadline: ";
    getline(cin, newTask.deadline);
    
    cout << "Enter task priority (1-5): ";
    cin >> newTask.priority;
    
    newTask.completed = false;
    
    tasks.push_back(newTask);
    
    cout << "Task added successfully!\n";
}

// Function to display all tasks
void displayTasks(const vector<Task>& tasks) {
    cout << "Tasks:\n";
    
    for (const Task& task : tasks) {
        cout << "Title: " << task.title << "\n";
        cout << "Description: " << task.description << "\n";
        cout << "Deadline: " << task.deadline << "\n";
        cout << "Priority: " << task.priority << "\n";
        cout << "Status: " << (task.completed ? "Completed" : "Incomplete") << "\n";
        cout << "-----------------\n";
    }
}

// Function to edit a task
void editTask(vector<Task>& tasks) {
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

// Function to delete a task
void deleteTask(vector<Task>& tasks) {
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

// Function to mark a task as completed
void markTaskCompleted(vector<Task>& tasks) {
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

// Function to save tasks to a file
void saveTasksToFile(const vector<Task>& tasks, const string& filename) {
    ofstream file(filename);

    for (const Task& task : tasks) {
        file << task.title << "\n";
        file << task.description << "\n";
        file << task.deadline << "\n";
        file << task.priority << "\n";
        file << task.completed << "\n";
    }

    file.close();
}

// Function to load tasks from a file
void loadTasksFromFile(vector<Task>& tasks, const string& filename) {
    ifstream file(filename);

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

        tasks.push_back(task);
    }

    file.close();
}

void task_runwindow(vector<Task>& tasks, const string& filename) {
    int choice;

    do {
        cout << "Menu:\n";
        cout << "1. Add Task\n";
        cout << "2. Display Tasks\n";
        cout << "3. Edit Task\n";
        cout << "4. Delete Task\n";
        cout << "5. Mark Task as Completed\n";
        cout << "6. Save and Quit\n";
        cout << "Enter your choice (1-6): ";
        cin >> choice;

        switch (choice) {
            case 1:
                addTask(tasks);
                break;
            case 2:
                displayTasks(tasks);
                break;
            case 3:
                editTask(tasks);
                break;
            case 4:
                deleteTask(tasks);
                break;
            case 5:
                markTaskCompleted(tasks);
                break;
            case 6:
                saveTasksToFile(tasks, filename);
                cout << "Tasks saved. Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 6.\n";
        }
    } while (choice != 6);
}
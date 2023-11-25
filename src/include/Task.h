// Task.h
#ifndef TASK_H
#define TASK_H

#include <string>
#include <ctime>
#include <fstream>
#include <sstream>

struct TaskNode {
    std::string title;
    std::string description;
    std::string deadline;
    int priority;
    bool completed;
    time_t creationDate;

    TaskNode* next;
};

class TaskManager {
public:
    TaskManager();
    ~TaskManager();

    void runMenu();

private:
    TaskNode* head;

    void addTask(const std::string& title, const std::string& description, const std::string& deadline, int priority);
    void listTasks();
    void deleteTask(const std::string& title);
    void editTask(const std::string& title);
    void markTaskCompleted(const std::string& title);
    void searchTasks(const std::string& keyword);
    void saveToFile();
    void loadFromFile();

    TaskNode* createTaskNode(const std::string& title, const std::string& description, const std::string& deadline, int priority);
    void insertTaskNode(TaskNode* newNode);
    void deleteTaskNode(TaskNode* nodeToDelete);
};

#endif // TASK_H

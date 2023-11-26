#include "include/Task.h"


int main() {
    vector<Task> tasks;
    const string task_filename = "storage/tasks.txt";

    loadTasksFromFile(tasks, task_filename);
    task_runwindow(tasks, task_filename);

    return 0;
}

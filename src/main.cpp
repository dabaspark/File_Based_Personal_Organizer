#include "include/Task.h"


int main() {
    vector<Task> tasks;
    const string filename = "tasks.txt";

    loadTasksFromFile(tasks, filename);

    task_runwindow(tasks, filename);

    return 0;
}

#include "include/Task.h"


int main() {
    const string task_filename = "storage/tasks.txt";

    TaskManager taskManager(task_filename);
    taskManager.runWindow();

    return 0;
}

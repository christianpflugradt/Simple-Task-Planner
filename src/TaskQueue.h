#pragma once

#include <string>
#include <vector>
#include "Task.h"

class TaskQueue {
    public:
        enum Prio {
            now,
            shortTerm,
            midTerm,
            longTerm
        };
        TaskQueue(std::string filename);
        int getNumberOfTasks();
        void printTop5();
        void finishTask(int number);
        void postponeTask(TaskQueue::Prio p, int number);
        void addTask(TaskQueue::Prio p, Task task);
    private:
        std::vector<Task> tasks;
        std::string filename;
        void deleteTask(int number);
        void insertTask(TaskQueue::Prio p, Task task);
        void persistTasks();
        void loadTasks();
};

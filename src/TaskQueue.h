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
        TaskQueue(std::string filename, int limit);
        int getNumberOfTasks();
        void printTopX();
        void finishTask(int number);
        void postponeTask(TaskQueue::Prio p, int number);
        void addTask(TaskQueue::Prio p, Task task);
    private:
        std::vector<Task> tasks;
        std::string filename;
        int limit;
        void deleteTask(int number);
        void insertTask(TaskQueue::Prio p, Task task);
        void persistTasks();
        void loadTasks();
};

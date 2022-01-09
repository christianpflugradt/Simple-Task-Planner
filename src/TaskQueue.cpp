#include <cstdlib>
#include <iostream>
#include <fstream>
#include "Task.h"
#include "TaskQueue.h"
#include "Util.h"

TaskQueue::TaskQueue(std::string filename) {
    this->filename = filename;
    loadTasks();
}

void TaskQueue::loadTasks() {
    std::fstream file;
    file.open(filename, std::ios::in);
    std::string line;
    while(std::getline(file, line)) {
        int start = 0;
        auto end = line.find("\t");
        int date = std::atoi(line.substr(start, end - start).c_str());
        start = end + 1;
        end = line.find("\t");
        int postponements = std::atoi(line.substr(start, end - start).c_str());
        start = end + 1;
        std::string title = line.substr(start);
        this->tasks.insert(this->tasks.end(), Task(date, postponements, title));
    }
    printTop5();
}

int TaskQueue::getNumberOfTasks() {
    return this->tasks.size();
}

void TaskQueue::printTop5() {
    int limit = std::min(5, getNumberOfTasks());
    Util::println("\nTop 5 tasks (" + std::to_string(getNumberOfTasks()) + " total)");
    for (int i=0; i<limit; i++) {
        Util::print(std::to_string(i + 1) + ". " + this->tasks.at(i).to_string() + "\n");
    }
    Util::println("");
}

void TaskQueue::finishTask(int number) {
    deleteTask(number);
    printTop5();
    persistTasks();
}

void TaskQueue::deleteTask(int number) {
    this->tasks.erase(this->tasks.begin() + number);
}

void TaskQueue::addTask(TaskQueue::Prio p, Task task) {
    insertTask(p, task);
    printTop5();
    persistTasks();
}

void TaskQueue::insertTask(TaskQueue::Prio p, Task task) {
    switch(p) {
        case TaskQueue::Prio::now:
            this->tasks.insert(this->tasks.begin(), task);
            break;
        case TaskQueue::Prio::shortTerm:
            this->tasks.insert(this->tasks.begin() + std::min(10, getNumberOfTasks()), task);
            break;
        case TaskQueue::Prio::midTerm:
            this->tasks.insert(this->tasks.begin() + std::min(std::max(20, getNumberOfTasks()/2), getNumberOfTasks()), task);
            break;
        case TaskQueue::Prio::longTerm:
            this->tasks.insert(this->tasks.end(), task);
            break;
     }
}

void TaskQueue::postponeTask(TaskQueue::Prio p, int number) {
    Task task(tasks.at(number));
    task.postpone();
    deleteTask(number);
    insertTask(p, task);
    printTop5();
    persistTasks();
}

void TaskQueue::persistTasks() {
    std::ofstream file;
    file.open(filename);
    for (int i = 0; i < this->tasks.size(); i++) {
        file << this->tasks.at(i).to_csv() << std::endl;
    }
    file.close();
}

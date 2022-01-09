#include "Task.h"
#include "Util.h"

Task::Task(int date, int postponements, const std::string title) {
    this->createDate = date;
    this->postponements = postponements;
    this->title = title;
}

Task::Task(const std::string title) {
    this->createDate = Util::now();
    this->postponements = 0;
    this->title = title;
}

void Task::postpone() {
    this->postponements++;
}

std::string Task::to_string() {
    return this->title + " "
        + std::to_string(Util::calcDays(this->createDate)) + "d "
        + std::to_string(this->postponements) + "x";
}

std::string Task::to_csv() {
    return std::to_string(this->createDate) + "\t"
        + std::to_string(this->postponements) + "\t"
        + this->title;
}

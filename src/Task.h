#pragma once

#include <string>

class Task {
    public:
        Task(const std::string title);
        Task(int date, int postponements, const std::string title);
        void postpone();
        std::string to_string();
        std::string to_csv();
    private:
        std::string title;
        int postponements;
        int createDate;
};

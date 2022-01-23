#include <cstdlib>
#include <cstring>
#include <regex>
#include <string>

#include "TaskQueue.h"
#include "Util.h"
#include "StpTexts.h"

class SimpleTaskPlanner {

    private:

        enum Mode {
            focus,
            normal,
            strategy
        };

    public:

        void run(std::string filename, std::string mode) {
            this->initMode(mode);
            this->taskQueue = new TaskQueue(filename, getLimit());
            StpTexts::printBanner();
            printRunInfo(filename);
            for(;;) {
                Util::print("your input: ");
                const std::string command = Util::getInput();
                if (command == QUIT) {
                    break;
                } else if (command == NOW || command == SHORT || command == MEDIUM || command == LONG) {
                    Util::print("enter task name: ");
                    const std::string task = Util::getInput();
                    if (task.empty()) {
                        Util::println("Input empty - aborted.");
                    } else {
                        taskQueue->addTask(inputToPrio(command), Task(task));
                    }
                } else if (isTopX(command)) {
                    modifyTopX(command);
                } else {
                    StpTexts::printUsage();
                    taskQueue->printTopX();
                }
            }
            Util::println("Bye!");
        }

    private:

        TaskQueue *taskQueue;
        Mode mode;

        const std::string QUIT = "Q";
        const std::string DONE = "D";
        const std::string NOW = "N";
        const std::string SHORT = "S";
        const std::string MEDIUM = "M";
        const std::string LONG = "L";

        int getLimit() {
            if (mode == Mode::focus) {
                return 3;
            } else if (mode == Mode::strategy) {
                return 9;
            } else {
                return 5;
            }
        }

        bool isTopX(std::string input) {
            return std::regex_match(input, std::regex("([" + Util::numericString(getLimit()) + "][DSML])"));
        }

        TaskQueue::Prio inputToPrio(std::string input) {
            if (input == NOW) {
                return TaskQueue::Prio::now;
            } else if (input == SHORT) {
                return TaskQueue::Prio::shortTerm;
            } else if (input == MEDIUM) {
                return TaskQueue::Prio::midTerm;
            } else if (input == LONG) {
                return TaskQueue::Prio::longTerm;
            } else {
                return TaskQueue::Prio::longTerm;
            }
        }

        void modifyTopX(std::string input) {
            int pos = std::atoi(input.substr(0,1).c_str()) - 1;
            if (taskQueue->getNumberOfTasks() <= pos) {
                Util::println("Task does not exist - aborted.");
            } else {
                std::string command = input.substr(1,1);
                if (command == DONE) {
                    taskQueue->finishTask(pos);
                } else {
                    taskQueue->postponeTask(inputToPrio(command), pos);
                }
            }
        }

        void initMode(std::string input) {
            if (input == "focus") {
                this->mode = Mode::focus;
            } else if (input == "strategy") {
                this->mode = Mode::strategy;
            } else {
                this->mode = Mode::normal;
            }
        }

        void printRunInfo(std::string filename) {
            Util::println("    using file '" + filename + "' for task list");
            if (mode == Mode::focus) {
                Util::println("    active mode: focus");
            } else if (mode == Mode::strategy) {
                Util::println("    active mode: strategy");
            }
            Util::println("    (just hit enter to display usage info)");
        }

};

int main(int argc, char *argv[]) {
    const std::string filename = argc > 1 ? std::string(argv[1]) : "stp.csv";
    const std::string mode = argc > 2 ? std::string(argv[2]) : "";
    SimpleTaskPlanner simpleTaskPlanner;
    simpleTaskPlanner.run(filename, mode);
}

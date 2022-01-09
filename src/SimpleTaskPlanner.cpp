#include <cstdlib>
#include <cstring>
#include <regex>
#include <string>

#include "TaskQueue.h"
#include "Util.h"

class SimpleTaskPlanner {

    public:

        void run(std::string filename) {
            printBanner();
            Util::println("    using file '" + filename + "' for task list");
            Util::println("    (just hit enter to display usage info)");
            taskQueue = new TaskQueue(filename);
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
                } else if (isTop5(command)) {
                    modifyTop5(command);
                } else {
                    printUsage();
                }
            }
            Util::println("Bye!");
        }

    private:

        TaskQueue *taskQueue;

        const std::string QUIT = "Q";
        const std::string DONE = "D";
        const std::string NOW = "N";
        const std::string SHORT = "S";
        const std::string MEDIUM = "M";
        const std::string LONG = "L";

        bool isTop5(std::string input) {
            return std::regex_match(input, std::regex("([12345][DSML])"));
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

        void modifyTop5(std::string input) {
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

        void printBanner() {
            Util::print(R"(
      _  _  _  _         _  _  _  _  _         _  _  _  _
    _(_)(_)(_)(_)_      (_)(_)(_)(_)(_)       (_)(_)(_)(_)_
   (_)          (_)           (_)             (_)        (_)
   (_)_  _  _  _              (_)             (_) _  _  _(_)
     (_)(_)(_)(_)_            (_)             (_)(_)(_)(_)
    _           (_)           (_)             (_)
   (_)_  _  _  _(_)           (_)             (_)
     (_)(_)(_)(_)             (_)             (_)

     SIMPLE                   TASK            PLANNER     v0.1.0


)");
        }

        void printUsage() {
            Util::print(R"(
    usage:

    - input Q (capital letter) to exit this program
    - input one of the following capital letters to create a new task:
        - N => creates a task to be done now (at position 1 in the list)
        - S => creates a task to be done short term (at position 11 or last in the list)
        - M => creates a task to be done mid term (right in the middle of the list
               but at least at position 21 or last in the list if it has less than 42 entries)
        - L => creates a task to be done long term (at last position in the list)
        - leave the task name empty to abort
    - input a command to update one of the top 5 in the list
        - 1D will set the 1st task to done (remove it from the list)
        - 2S will move the 2nd task to short term (same ruleset as for new tasks applies)
        - 3M will move the 3rd task to mid term (same ruleset as for new tasks applies)
        - 4L will move the 4th task to long term (same ruleset as for new tasks applies)
        - any of the positions 1, 2, 3, 4 and 5 can be combined with any of the letters D, S, M and L
    - top 5
        - after every action the top 5 will be displayed
            - it is not possible to view any other tasks, you always have to deal with your top 5
            - each task is suffixed with something like '3d 1x'
                - d and x are always fix but the numbers vary
                - 3d indicates the task exist since 3 days
                - 1x indicates the task has been postponed once (using a command such as 2S)
                - more examples:
                    - '0d 0x' means the task is less than a day old and hasn't been postponed
                    - '365d 8x' means the task is a year old and has been postponed 8 times
    - the task list is synchronized to a csv file
        - the physical file is updated immediately after every action
        - the default file name is 'stp.csv'
        - you may pass another file name as program argument to use it instead,
          if the file doesn't exist it will be created upon program start
        - example program call for a custom file '/tmp/mytasks.csv' => './runSimpleTaskPlanner.sh /tmp/mytasks.csv'
    - think before you act: any actions performed cannot be easily undone
    - enter anything else to display this usage info

)");
        }

};

int main(int argc, char *argv[]) {
    const std::string filename = argc > 1 ? std::string(argv[1]) : "stp.csv";
    SimpleTaskPlanner simpleTaskPlanner;
    simpleTaskPlanner.run(filename);
}

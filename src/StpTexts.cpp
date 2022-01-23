#include "StpTexts.h"
#include "Util.h"

void StpTexts::printBanner() {
    Util::print(R"(

     Copyright 2022 Christian Pflugradt
     This software is licensed under the Apache License, Version 2.0 (APLv2)
     You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

      _  _  _  _         _  _  _  _  _         _  _  _  _
    _(_)(_)(_)(_)_      (_)(_)(_)(_)(_)       (_)(_)(_)(_)_
   (_)          (_)           (_)             (_)        (_)
   (_)_  _  _  _              (_)             (_) _  _  _(_)
     (_)(_)(_)(_)_            (_)             (_)(_)(_)(_)
    _           (_)           (_)             (_)
   (_)_  _  _  _(_)           (_)             (_)
     (_)(_)(_)(_)             (_)             (_)

     SIMPLE                   TASK            PLANNER     v0.2.0

)");
}

void StpTexts::printUsage() {
                Util::print(R"(
        usage:

        * input Q (capital letter) to exit this program

        * input one of the following capital letters to create a new task:
            - N => creates a task to be done now (at position 1 in the list)
            - S => creates a task to be done short term (at position 10)
            - M => creates a task to be done mid term (right in the middle of the list
                   but at least at position 20 in the list if it has less than 40 entries)
            - L => creates a task to be done long term (at last position in the list)
            - leave the task name empty to abort

        * input a command to update one of the top 5 in the list
            - 1D will set the 1st task to done (remove it from the list)
            - 2S will move the 2nd task to short term (same ruleset as for new tasks applies)
            - 3M will move the 3rd task to mid term (same ruleset as for new tasks applies)
            - 4L will move the 4th task to long term (same ruleset as for new tasks applies)
            - any of the positions 1, 2, 3, 4 and 5 can be combined with any of the letters D, S, M and L

        * top 5
            - after every action the top 5 will be displayed
                - it is not possible to view any other tasks, you always have to deal with your top 5
                - each task is suffixed with something like '3d 1x'
                    - d and x are always fix but the numbers vary
                    - 3d indicates the task exist since 3 days
                    - 1x indicates the task has been postponed once (using a command such as 2S)
                    - more examples:
                        - '0d 0x' means the task is less than a day old and hasn't been postponed
                        - '365d 8x' means the task is a year old and has been postponed 8 times

        * the task list is synchronized to a csv file
            - the physical file is updated immediately after every action
            - the default file name is 'stp.csv'
            - you may pass another file name as program argument to use it instead,
              if the file doesn't exist it will be created upon program start
            - example program call for a custom file '/tmp/mytasks.csv' => './runSTP.sh /tmp/mytasks.csv'

        * in addition to a csv file name you may specify a mode
            - the mode is given as second parameter and can only be specified when explicitly specifying a csv file name
            - the mode 'focus' replaces the 'top 5' with a 'top 3', allowing to concentrate on only these most important tasks
            - the mode 'strategy' replaces the 'top 5' with a 'top 9', allowing to focus on more tasks at the same time
            - example program call => './runSTP.sh stp.csv strategy'

        * think before you act: any actions performed cannot be easily undone
        * enter anything else to display this usage info

    )");
}

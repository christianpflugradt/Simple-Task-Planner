gcc -std=c++17 src/Util.cpp src/StpTexts.cpp src/Task.cpp src/TaskQueue.cpp src/SimpleTaskPlanner.cpp -o STP -lstdc++ -lm
chmod +x STP
./STP $1 $2


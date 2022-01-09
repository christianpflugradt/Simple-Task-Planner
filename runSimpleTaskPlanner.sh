gcc -std=c++17 src/Util.cpp src/Task.cpp src/TaskQueue.cpp src/SimpleTaskPlanner.cpp -o SimpleTaskPlanner -lstdc++ -lm
chmod +x SimpleTaskPlanner
./SimpleTaskPlanner $1

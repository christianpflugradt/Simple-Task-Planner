# Simple Task Planner

Simple Task Planner (STP) is a very simple command line based tool to organize tasks.

## Description

STP manages a list of tasks. A task is represented as a plain string. Tasks can be added with different priorities, putting them at the beginning, near the beginning, in the middle or at the very end of the list of tasks. STP only shows the top 5 tasks which can be finished or postponed to make space for tasks further back in the list.

The most important feature about the tool is that the list of tasks is synchronized with a local csv file. The file may be edited outside the use of STP to view or update tasks that are not in the top 5.

## How to run

You need gcc to run `./runSTP.sh` which will compile STP from source and launch it. If you know C++, feel free to change the script to use another compiler.

You can pass a csv file as program argument to manage multiple task lists. Assuming you want to (create and) use a file named `/tmp/my-tasks.csv` you can invoke the script as follows: `./runSTP.sh /tmp/my-tasks.csv`

## Development

This program is very basic and suited to my personal needs. It'll likely be improved in the future but stays mostly basic.

//
// Created by Bryce Callender on 2019-10-03.
//

#ifndef TASKSCHEDULER_TASK_H
#define TASKSCHEDULER_TASK_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

struct Job
{
    std::string name = "";
    int burstTime = 0;

    int startTime = 0;
    int endTime = 0;
};

class Task
{
public:
    void readJobFile(std::vector<Job>& jobs);
    void printScheduleTable(const std::vector<Job>& jobs);
};


#endif //TASKSCHEDULER_TASK_H

#pragma once

#include "Task.h"

class FirstComeFirstServed : public Task
{
public:
    FirstComeFirstServed() = default;

    double firstComeFirstServedAlgorithm()
    {
        std::cout << "Performing First Come First Serve Algorithm!\n";

        std::vector<Job> jobs;

        //Read the file to get the job information
        readJobFile(jobs);

        int timer = 0;
        double averageTurnAroundTime = 0.0;

        //For each job in the list
        for (Job& currentJob : jobs)
        {
            //Make the job's start time based on the current timer
            currentJob.startTime = timer;

            //Add the burst time to the timer and retire the job
            timer += currentJob.burstTime;
            currentJob.burstTime = 0;

            //End the job at this time and add the time to the averageTimer
            currentJob.endTime = timer;
            averageTurnAroundTime += currentJob.endTime;
        }

        //Print the Schedule Table
        printScheduleTable(jobs);

        //Return the average time
        return averageTurnAroundTime / jobs.size();
    }
};
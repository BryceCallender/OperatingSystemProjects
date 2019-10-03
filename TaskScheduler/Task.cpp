#include <limits>
#include "Task.h"

void Task::readJobFile(std::vector<Job>& jobs)
{
    std::ifstream inputFile("/Users/brycecallender/CLionProjects/TaskScheduler/job.txt");

    while (!inputFile.eof())
    {
        //Read in the job name
        std::string name;
        std::getline(inputFile, name);

        //Read in the burst time
        int burstTime;
        inputFile >> burstTime;

        //Clean input buffer
        inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        //Make the job
        Job job;
        job.name = name;
        job.burstTime = burstTime;

        //Add it to the vector
        jobs.push_back(job);
    }

    inputFile.close();
}

void Task::printScheduleTable(const std::vector<Job>& jobs)
{
    //Prints out the table headers
    std::cout << std::left << std::setw(12) << "Job Name" << std::setw(14) << "Start Time" << std::setw(12) << "End Time" << std::setw(19) << "Job Completion" << std::endl;
    //For each job in the job list
    for(const Job& job : jobs)
    {
        //Print out thye name, starting time, end time
        std::cout << std::left << std::setw(12) << job.name << std::setw(14) << job.startTime << std::setw(12) << job.endTime;
        //If the job is completed print out that it completed @end time
        if(job.burstTime == 0)
        {
            std::cout << std::setw(19) << job.name + " completed at @" + std::to_string(job.endTime);
        }
        std::cout << std::endl;
    }
}



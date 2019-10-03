#include <iostream>
#include <random>
#include "FirstComeFirstServed.h"
#include "ShortestJobFirst.h"
#include "RoundRobin.h"

void generateRandomJobsInFile(int jobCount);
void printAverageTime(double time);

int main()
{
    FirstComeFirstServed firstComeFirstServed;
    ShortestJobFirst shortestJobFirst;
    RoundRobin roundRobin;

    std::cout << std::endl;

    printAverageTime(firstComeFirstServed.firstComeFirstServedAlgorithm());
    printAverageTime(shortestJobFirst.shortestJobFirst());
    printAverageTime(roundRobin.roundRobin(2));
    printAverageTime(roundRobin.roundRobin(5));

	return 0;
}

void generateRandomJobsInFile(int jobCount)
{
    std::ofstream jobTextFile("/Users/brycecallender/CLionProjects/TaskScheduler/job.txt");

    std::random_device randomDevice;  //Will be used to obtain a seed for the random number engine
    std::mt19937 generator(randomDevice()); //Standard mersenne_twister_engine seeded with randomDevice()
    std::uniform_int_distribution<> dis(1, 30);

    for(int i = 0; i < jobCount; i++)
    {
        jobTextFile << "Job" + std::to_string(i + 1) << std::endl; //Write Job name to the text file
        if(i < jobCount - 1)
        {
            jobTextFile << dis(generator) << std::endl;
        }
        else
        {
            jobTextFile << dis(generator);
        }
    }

    jobTextFile.close();
}

void printAverageTime(double time)
{
    std::cout << "\nThe average turn around time is: " << time << std::endl << std::endl;
}



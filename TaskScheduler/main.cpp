#include <iostream>
#include <random>
#include <string>
#include <fstream>
#include <iomanip>

struct Job
{
	std::string name = "";
	int burstTime = 0;

	int startTime = 0;
	int endTime = 0;
};

#include "FirstComeFirstServed.h"
#include "ShortestJobFirst.h" 
#include "RoundRobin.h"

void generateRandomJobsInFile(int jobCount);
void printAverageTime(double time);

const int NUM_TESTS = 15;
static int array[] = { 5, 10, 15, 20, 25, 30 };

int main()
{
    FirstComeFirstServed firstComeFirstServed;
    ShortestJobFirst shortestJobFirst;
    RoundRobin roundRobin;

    std::cout << std::endl;
	
	double totalFCFSTime = 0;
	double totalSJFTime = 0;
	double totalRoundRobin2Time = 0;
	double totalRoundRobin5Time = 0;
	
	for (int jobSize : array)
	{
		for(int j = 0; j < NUM_TESTS; j++)
		{
			generateRandomJobsInFile(jobSize);

			double average = 0;

			average = firstComeFirstServed.firstComeFirstServedAlgorithm();
			std::cout << "The average turnaround time is: " << average << std::endl << std::endl;
			totalFCFSTime += average;
			
			average = shortestJobFirst.shortestJobFirst();
			std::cout << "The average turnaround time is: " << average << std::endl << std::endl;
			totalSJFTime += average;
			
			average = roundRobin.roundRobin(2);
			std::cout << "The average turnaround time is: " << average << std::endl << std::endl;
			totalRoundRobin2Time += average;
			
			average = roundRobin.roundRobin(5);
			std::cout << "The average turnaround time is: " << average << std::endl << std::endl;
			totalRoundRobin5Time += average;
			
		}

		std::cout << "The average time for FCFS" << " of size " << jobSize << ": " << totalFCFSTime / NUM_TESTS << std::endl;
		std::cout << "The average time for SJF" << " of size " << jobSize << ": " << totalSJFTime / NUM_TESTS << std::endl;
		std::cout << "The average time for RR-2" << " of size " << jobSize << ": " << totalRoundRobin2Time / NUM_TESTS << std::endl;
		std::cout << "The average time for RR-5" << " of size " << jobSize << ": " << totalRoundRobin5Time / NUM_TESTS << std::endl;

		totalFCFSTime = 0;
		totalSJFTime = 0;
		totalRoundRobin2Time = 0;
		totalRoundRobin5Time = 0;

		std::cout << std::endl << std::endl;
		system("pause");

		std::cout << std::endl << std::endl;
	}

	return 0;
}

void generateRandomJobsInFile(int jobCount)
{
    std::ofstream jobTextFile("job.txt");

    std::random_device randomDevice;  //Will be used to obtain a seed for the random number engine
    std::mt19937 generator(randomDevice()); //Standard mersenne_twister_engine seeded with randomDevice()
    std::uniform_int_distribution<> dis(1, 30);

    for(int i = 0; i < jobCount; i++)
    {
        jobTextFile << "Job" + std::to_string(i + 1) << std::endl; //Write Job name to the text file
        if(i < jobCount - 1)
        {
            jobTextFile << dis(generator) << std::endl; //write number and a newline, more to come
        }
        else
        {
            jobTextFile << dis(generator); //Last number to generate just output the number to the file
        }
    }

    jobTextFile.close();
}

void printAverageTime(const double time)
{
    std::cout << "\nThe average turn around time is: " << time << std::endl << std::endl;
}



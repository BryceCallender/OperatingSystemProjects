#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>

struct Job
{
	std::string name = "";
	int burstTime = 0;

	int startTime = 0;
	int endTime = 0;
};

double firstComeFirstServedAlgorithm();
double shortestJobFirst();
double roundRobin(int roundRobinSlice);

void readJobFile(std::vector<Job>& jobs);
void printScheduleTable(const std::vector<Job>& jobs);

int main()
{
	std::cout << "The average turn around time is: " << firstComeFirstServedAlgorithm() << std::endl << std::endl;

	std::cout << "The average turn around time is: " << shortestJobFirst() << std::endl << std::endl;

	std::cout << "The average turn around time is: " << roundRobin(2) << std::endl << std::endl;

	std::cout << "The average turn around time is: " << roundRobin(3) << std::endl << std::endl;

	return 0;
}

void readJobFile(std::vector<Job>& jobs)
{
	std::ifstream inputFile("/Users/brycecallender/CLionProjects/TaskScheduler/job.txt");
	
	while (!inputFile.eof())
	{
		std::string name;
		std::getline(inputFile, name);

		int burstTime;
		inputFile >> burstTime;

		inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		Job job;
		job.name = name;
		job.burstTime = burstTime;

		jobs.push_back(job);
	}

	inputFile.close();
}

void printScheduleTable(const std::vector<Job>& jobs)
{
	std::cout << std::left << std::setw(12) << "Job Name" << std::setw(14) << "Start Time" << std::setw(12) << "End Time" << std::setw(19) << "Job Completion" << std::endl;
	for(const Job& job : jobs)
	{
		std::cout << std::left << std::setw(12) << job.name << std::setw(14) << job.startTime << std::setw(12) << job.endTime;
		if(job.burstTime == 0)
        {
            std::cout << std::setw(19) << job.name + " completed at @" + std::to_string(job.endTime);
        }
		std::cout << std::endl;
	}
} 

double firstComeFirstServedAlgorithm()
{
	std::vector<Job> jobs;

	readJobFile(jobs);

	int timer = 0;
	double averageTurnAroundTime = 0.0;

	for (Job& currentJob : jobs)
	{
        currentJob.startTime = timer;

		timer += currentJob.burstTime;
		currentJob.burstTime = 0;

		currentJob.endTime = timer;
		averageTurnAroundTime += currentJob.endTime;
	}

	printScheduleTable(jobs);
	
	return averageTurnAroundTime / jobs.size();
}

double shortestJobFirst()
{
	std::vector<Job> jobs;

	readJobFile(jobs);

	std::sort(jobs.begin(), jobs.end(), [](Job a, Job b)
	{
		return a.burstTime < b.burstTime;
	});

	int timer = 0;
	double averageTurnAroundTime = 0.0;

	for (Job& currentJob : jobs)
	{
        currentJob.startTime = timer;

		timer += currentJob.burstTime;
        currentJob.burstTime = 0;

		currentJob.endTime = timer;
		averageTurnAroundTime += currentJob.endTime;
	}

	printScheduleTable(jobs);

	return averageTurnAroundTime / jobs.size();
	
}

double roundRobin(int roundRobinSlice)
{
	std::vector<Job> jobs;

	readJobFile(jobs);

	std::vector<Job> jobList = jobs;

	int timer = 0;
	int jobSize = jobs.size();
	double averageTurnAroundTime = 0.0;
	int index = 0;

    while(!jobs.empty())
    {
        Job& currentJob = jobList[index];
        currentJob.startTime = timer;

        //Does the current job not require all of the round robin time?
        if(currentJob.burstTime - roundRobinSlice < 0)
        {
            timer += currentJob.burstTime;
            //Get rid of the correct job based on index we are (circularly)
            currentJob.endTime = timer;
            currentJob.burstTime = 0;
            averageTurnAroundTime += currentJob.endTime;
            jobs.erase(jobs.begin() + (index % jobSize));
        }
        //Does it take all the time?
        else if(currentJob.burstTime - roundRobinSlice == 0)
        {
            timer += roundRobinSlice;
            currentJob.burstTime = 0;
            currentJob.endTime = timer;
            averageTurnAroundTime += currentJob.endTime;
            //jobList.push_back(currentJob);
            //Get rid of the front of the list of jobs
            jobs.erase(jobs.begin() + (index % jobSize));
        }
        //Does it have time left?
        else
        {
            timer += roundRobinSlice;
            currentJob.burstTime -= roundRobinSlice;
            currentJob.endTime = timer;
            jobList.push_back(currentJob);
        }
        index++;
    }

    printScheduleTable(jobList);

    return averageTurnAroundTime / jobSize;
	
}

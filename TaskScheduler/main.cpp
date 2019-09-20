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
	std::ifstream inputFile("job.txt");
	
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
		std::cout << std::left << std::setw(12) << job.name << std::setw(14) << job.startTime << std::setw(12) << job.endTime << std::setw(19) << job.name + " completed at @" + std::to_string(job.endTime);
		std::cout << std::endl;
	}
} 

double firstComeFirstServedAlgorithm()
{
	std::vector<Job> jobs;

	readJobFile(jobs);

	int timer = 0;
	double averageTurnAroundTime = 0.0;

	for (int i = 0; i < jobs.size(); i++)
	{
		Job& currentJob = jobs[i];
		currentJob.startTime = timer;

		timer += currentJob.burstTime;

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

	for (int i = 0; i < jobs.size(); i++)
	{
		Job& currentJob = jobs[i];
		currentJob.startTime = timer;

		timer += currentJob.burstTime;

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

	int timer = 0;
	double averageTurnAroundTime = 0.0;

	
}

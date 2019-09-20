#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

struct Job
{
	std::string name = "";
	int burstTime = 0;

	int startTime = 0;
	int endTime = 0;
};

double firstComeFirstServedAlgorithm(std::ifstream& inputFile);


int main()
{
	std::ifstream inputFile("job.txt");

	std::cout << firstComeFirstServedAlgorithm(inputFile);

	inputFile.close();
	return 0;
}

double firstComeFirstServedAlgorithm(std::ifstream& inputFile)
{
	std::vector<Job> jobs;

	while(!inputFile.eof())
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

	int timer = 0;
	int index = 0;
	Job currentJob = jobs[index];
	currentJob.startTime = timer;
	while (index < jobs.size())
	{
		if(currentJob.burstTime == 0)
		{
			currentJob.endTime = timer;
			index++;
			if (index == jobs.size())
				break;
			currentJob = jobs[index];
			currentJob.startTime = timer;
		}
			
		timer++;
		currentJob.burstTime--;
	}

	double averageTurnAroundTime = 0.0;
	for (Job job : jobs)
	{
		averageTurnAroundTime += job.endTime;
	}

	return averageTurnAroundTime / jobs.size();
}

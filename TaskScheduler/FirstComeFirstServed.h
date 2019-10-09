#pragma once

class FirstComeFirstServed
{
public:
    FirstComeFirstServed() = default;

    double firstComeFirstServedAlgorithm()
    {
        //std::cout << "Performing First Come First Serve Algorithm!\n";

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
        //printScheduleTable(jobs);

        //Return the average time
        return averageTurnAroundTime / jobs.size();
    }

	void readJobFile(std::vector<Job>& jobs)
	{
		std::ifstream inputFile("job.txt");

		while (!inputFile.eof())
		{
			//Read in the job name
			std::string name;
			std::getline(inputFile, name);

			if(name.empty())
			{
				break;
			}

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

	void printScheduleTable(const std::vector<Job>& jobs)
	{
		//Prints out the table headers
		std::cout << std::left << std::setw(12) << "Job Name" << std::setw(14) << "Start Time" << std::setw(12) << "End Time" << std::setw(19) << "Job Completion" << std::endl;
		//For each job in the job list
		for (const Job& job : jobs)
		{
			//Print out thye name, starting time, end time
			std::cout << std::left << std::setw(12) << job.name << std::setw(14) << job.startTime << std::setw(12) << job.endTime;
			//If the job is completed print out that it completed @end time
			if (job.burstTime == 0)
			{
				std::cout << std::setw(19) << job.name + " completed at @" + std::to_string(job.endTime);
			}
			std::cout << std::endl;
		}
	}

};

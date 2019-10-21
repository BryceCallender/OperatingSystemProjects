#pragma once

class RoundRobin
{
public:
    RoundRobin() = default;

    double roundRobin(int roundRobinSlice)
    {
        std::cout << "Performing Round Robin with time slice " + std::to_string(roundRobinSlice) + " or RR-" + std::to_string(roundRobinSlice) << std::endl;

        std::vector<Job> jobs;

        //Read the jobs from the file
        readJobFile(jobs);

        //Make a copy of the job list so we can keep adding to it
        std::vector<Job> jobList = jobs;

        int timer = 0;
        double averageTurnAroundTime = 0.0;
        int tasksRemoved = 0;
        int index = 0;

        //While we have tasks to be done still
        while(tasksRemoved != jobs.size())
        {
            //Get the job at the current index of the list and set its starting time
            Job& currentJob = jobList[index];
            currentJob.startTime = timer;

            //Does the current job not require all of the round robin time?
            if(currentJob.burstTime - roundRobinSlice < 0)
            {
                //Add to the timer the burst time we have left
                timer += currentJob.burstTime;
                //Set the ending time and retire the job
                currentJob.endTime = timer;
                currentJob.burstTime = 0;
                //Add to the average time and increment since a job was removed
                averageTurnAroundTime += currentJob.endTime;
                tasksRemoved++;
            }
            //Does it take all the time?
            else if(currentJob.burstTime - roundRobinSlice == 0)
            {
                //Add the slice time to the timer since it used all the time
                timer += roundRobinSlice;
                //Retire the job and set its ending time
                currentJob.burstTime = 0;
                currentJob.endTime = timer;
                //Add to the average time and increment since a job was removed
                averageTurnAroundTime += currentJob.endTime;
                tasksRemoved++;
            }
            //Does it have time left?
            else
            {
                //Increment timer since it used all the time
                timer += roundRobinSlice;
                //Take away the burst time by slice amount
                currentJob.burstTime -= roundRobinSlice;
                //The job will be switched out so set the end time of the job to right now and add it to the back of the list
                currentJob.endTime = timer;
                jobList.push_back(currentJob);
            }
            //Next job
            index++;
        }

        //Print the Schedule Table
        printScheduleTable(jobList);

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

			if (name.empty())
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
		std::cout << std::endl;
	}
};
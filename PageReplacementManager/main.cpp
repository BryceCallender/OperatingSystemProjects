#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include "FIFO.h"
#include "LRU.h"
#include "Optimal.h"

std::string generateRandomPageString();

const double NUM_TESTS = 50.0;

int PAGE_FRAME_SIZES[] = { 3, 4, 5, 6 };

int main()
{
    int totalFIFOFaults = 0;
    int totalLRUFaults = 0;
    int totalOptimalFaults = 0;

	FIFO fifo;
	LRU lru;
	Optimal optimal;

	//The file containing the reference strings used for the algorithms
	//It doesn't not contain the files to read as they are randomly generated
	//This is if you want to read the strings used by the algorithms as it saves
	//the strings to a file after being used
	std::ofstream refStringFile("ReferenceStrings.txt");

    for(int pageFrameSize : PAGE_FRAME_SIZES)
    {
		refStringFile << "Page Frame Size: " << pageFrameSize << std::endl;
        for(int i = 0; i < NUM_TESTS; i++)
        {
			std::string referenceString = generateRandomPageString();

        	//Record the reference string to the file
			refStringFile << referenceString << std::endl;
        	//Output it for reference in the output
			std::cout << "Reference string: " << referenceString << std::endl;
        	
			int result = fifo.firstInFirstOut(pageFrameSize, referenceString);
            totalFIFOFaults += result;

            result = lru.leastRecentlyUsed(pageFrameSize, referenceString);
            totalLRUFaults += result;
        	
            result = optimal.optimalAlgorithm(pageFrameSize, referenceString);
            totalOptimalFaults += result;
        }

    	//Output all the averages
		std::cout << std::endl;
        std::cout << "The average time for FIFO of page frame size " << pageFrameSize << ": " << totalFIFOFaults / NUM_TESTS << std::endl;
        std::cout << "The average time for LRU of page frame size " << pageFrameSize << ": " << totalLRUFaults / NUM_TESTS << std::endl;
        std::cout << "The average time for Optimal of page frame size " << pageFrameSize << ": " << totalOptimalFaults / NUM_TESTS << std::endl;

    	//Reset all the counters!
        totalFIFOFaults = 0;
        totalLRUFaults = 0;
        totalOptimalFaults = 0;

        std::cout << std::endl << std::endl;
		refStringFile << std::endl << std::endl;

		system("pause");
    }

	return 0;
}

std::string generateRandomPageString()
{
	std::random_device randomDevice;  //Will be used to obtain a seed for the random number engine
	std::mt19937 generator(randomDevice()); //Standard mersenne_twister_engine seeded with randomDevice()
	std::uniform_int_distribution<> dis(0, 7); //Will generate a random number from 0 to 7 (inclusive)

	std::string referenceString;

	for (int i = 0; i < 30; i++)
	{
		referenceString += std::to_string(dis(generator)); //generate a number and add it to the string
	}

	return referenceString;
}


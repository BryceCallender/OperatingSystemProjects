#include <iostream>
#include <string>
#include <random>
#include <fstream>

std::string generateRandomPageString();

int firstInFirstOut(int pageFrameSize, std::string& referenceString);
int leastRecentlyUsed(int pageFrameSize, std::string& referenceString);
int optimalAlgorithm(int pageFrameSize, std::string& referenceString);

bool isInPageBuffer(std::vector<int>& buffer, int pageNumber);

int main()
{
	std::string test = "70120304230321201701";

	std::cout << "There were " << firstInFirstOut(3, test) << " page faults!" << std::endl;
	
	return 0;
}

int firstInFirstOut(int pageFrameSize, std::string& referenceString)
{
	int numPageFaults = 0;

	int firstInIndex = 0;

	std::vector<int> pages(pageFrameSize, -1);

	for (char i : referenceString)
	{
		int pageNumber = i - '0';
		if(!isInPageBuffer(pages, pageNumber))
		{
			pages[firstInIndex] = pageNumber;
			numPageFaults++;
			firstInIndex = (firstInIndex + 1) % pageFrameSize;
		}
	}

	return numPageFaults;
}

int leastRecentlyUsed(int pageFrameSize, std::string& referenceString)
{
	int numPageFaults = 0;

	return numPageFaults;
}

int optimalAlgorithm(int pageFrameSize, std::string& referenceString)
{
	int numPageFaults = 0;

	return numPageFaults;
}

bool isInPageBuffer(std::vector<int>& buffer, int pageNumber)
{
	for (int element : buffer)
	{
		if(element == pageNumber)
		{
			return true;
		}
	}
	return false;
}

std::string generateRandomPageString()
{
	std::random_device randomDevice;  //Will be used to obtain a seed for the random number engine
	std::mt19937 generator(randomDevice()); //Standard mersenne_twister_engine seeded with randomDevice()
	std::uniform_int_distribution<> dis(0, 9);

	std::string referenceString;

	for (int i = 0; i < 30; i++)
	{
		referenceString += std::to_string(dis(generator)); //generate a number and add it to the string
	}

	return referenceString;
}


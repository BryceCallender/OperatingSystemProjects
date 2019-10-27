#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <unordered_map>

std::string generateRandomPageString();

int firstInFirstOut(int pageFrameSize, std::string& referenceString);
int leastRecentlyUsed(int pageFrameSize, std::string& referenceString);
int optimalAlgorithm(int pageFrameSize, std::string& referenceString);

bool isInPageBuffer(std::vector<int>& buffer, int pageNumber);
bool isPageVectorFull(std::vector<int>& buffer);
bool hasOnePageLeft(std::unordered_map<char, int>& buffer);

int main()
{
	std::string test = "70120304230321201701";

	std::cout << "There were " << firstInFirstOut(3, test) << " page faults!" << std::endl;

	std::cout << "There were " << leastRecentlyUsed(3, test) << " page faults!" << std::endl;

	std::cout << "There were " << optimalAlgorithm(3, test) << " page faults!" << std::endl;
	
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

	std::vector<int> pages(pageFrameSize, -1);
	std::vector<int> leastRecentlyUsed;

	int placeIndex = 0;

	for (char i : referenceString)
	{
		int pageNumber = i - '0';
		// If the number is not in pages then add it and that is a page fault
		if(!isInPageBuffer(pages, pageNumber))
		{
			// If the vector is not full yet
			if(!isPageVectorFull(pages))
			{
				// Place the number
				pages[placeIndex] = pageNumber;
				placeIndex++;
			}
			else
			{
				// The least recent item is always going to be at the front
				int pageToRemove = leastRecentlyUsed.front();

				leastRecentlyUsed.erase(leastRecentlyUsed.begin());

				// Find the page that is in the LRU and find out where it is in the pages list
				std::vector<int>::iterator iterator = std::find(pages.begin(), pages.end(), pageToRemove);

				// Change that number to the current page being added
				pages[std::distance(pages.begin(), iterator)] = pageNumber;
			}

			leastRecentlyUsed.push_back(pageNumber);
			numPageFaults++;
			
		}
		// The number is in pages so lets modify it to be recent in the vector 
		else
		{
			std::vector<int>::iterator iterator = std::find(leastRecentlyUsed.begin(), leastRecentlyUsed.end(), pageNumber);
			
			if(iterator != leastRecentlyUsed.end())
			{
				// Erase the one in the list already
				leastRecentlyUsed.erase(iterator);
				// Add it to the back to simulate it being recently used
			}
			
			leastRecentlyUsed.push_back(pageNumber);
		}
	}

	return numPageFaults;
}

int optimalAlgorithm(int pageFrameSize, std::string& referenceString)
{
	int numPageFaults = 0;

	std::vector<int> pages(pageFrameSize, -1);

	int placeIndex = 0;
	
	for(int i = 0; i < referenceString.length(); i++)
	{
		int pageNumber = referenceString[i] - '0';
		// If the number is not in pages then add it and that is a page fault
		if (!isInPageBuffer(pages, pageNumber))
		{
			// If the vector is not full yet
			if (!isPageVectorFull(pages))
			{
				// Place the number
				pages[placeIndex] = pageNumber;
				placeIndex++;
			}
			// Current page is not the buffer but the page vector is full
			else
			{
				std::unordered_map<char, int> currentPages;

				// Add the pages to the map so we know what we need
				for (int page : pages)
				{
					currentPages.insert(std::make_pair(page, 1));
				}

				int j = i;
				int currentPageNumber = pageNumber;
				// Loop until we find the one with the longest period of time until it appears
				while(j < referenceString.length() && !hasOnePageLeft(currentPages))
				{
					if (currentPages.find(pageNumber) != currentPages.end())
					{
						if (currentPages[pageNumber] > 0)
						{
							currentPages[pageNumber]--;
						}
					}
					
					pageNumber = referenceString[j] - '0';
					j++;
				}

				int pageToRemove = -1;

				// Find what the number is since there exists a number with a 1 in the map
				for (auto pair : currentPages)
				{
					if(pair.second == 1)
					{
						pageToRemove = pair.first;
					}
				}

				// Find the page that is in the LRU and find out where it is in the pages list
				std::vector<int>::iterator iterator = std::find(pages.begin(), pages.end(), pageToRemove);

				// Change that number to the current page being added
				pages[std::distance(pages.begin(), iterator)] = currentPageNumber;
							
			}

			numPageFaults++;
		}
	}
	
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

bool isPageVectorFull(std::vector<int>& buffer)
{
	for (int element : buffer)
	{
		if(element == -1)
		{
			return false;
		}
	}
	
	return true;
}

bool hasOnePageLeft(std::unordered_map<char, int>& buffer)
{
	int numOnes = 0;
	for(auto pair : buffer)
	{
		if(pair.second == 1)
		{
			numOnes++;
		}
	}

	return numOnes == 1;
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


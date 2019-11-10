#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <unordered_map>
#include <algorithm>

std::string generateRandomPageString();

int firstInFirstOut(int pageFrameSize, std::string& referenceString);
int leastRecentlyUsed(int pageFrameSize, std::string& referenceString);
int optimalAlgorithm(int pageFrameSize, std::string& referenceString);

bool isInPageBuffer(std::vector<int>& buffer, int pageNumber);
bool isPageVectorFull(std::vector<int>& buffer);
bool hasOnePageLeft(std::unordered_map<char, int>& buffer);

void printPages(std::vector<int>& buffer);

const double NUM_TESTS = 50.0;

int PAGE_FRAME_SIZES[] = { 3, 4, 5, 6 };

int main()
{
    int totalFIFOFaults = 0;
    int totalLRUFaults = 0;
    int totalOptimalFaults = 0;

	//The file containing the reference strings used for the algorithms
	std::ofstream refStringFile("ReferenceStrings.txt");

    for(int pageFrameSize : PAGE_FRAME_SIZES)
    {
		refStringFile << "Page Frame Size: " << pageFrameSize << std::endl;
        for(int i = 0; i < NUM_TESTS; i++)
        {
            std::string referenceString = generateRandomPageString();
			refStringFile << referenceString << std::endl;
        	
			int result = firstInFirstOut(pageFrameSize, referenceString);
            totalFIFOFaults += result;

            result = leastRecentlyUsed(pageFrameSize, referenceString);
            totalLRUFaults += result;
        	
            result = optimalAlgorithm(pageFrameSize, referenceString);
            totalOptimalFaults += result;
        }

        std::cout << "The average time for FIFO of page frame size " << pageFrameSize << ": " << totalFIFOFaults / NUM_TESTS << std::endl;
        std::cout << "The average time for LRU of page frame size " << pageFrameSize << ": " << totalLRUFaults / NUM_TESTS << std::endl;
        std::cout << "The average time for Optimal of page frame size " << pageFrameSize << ": " << totalOptimalFaults / NUM_TESTS << std::endl;

        totalFIFOFaults = 0;
        totalLRUFaults = 0;
        totalOptimalFaults = 0;

        std::cout << std::endl << std::endl;
		refStringFile << std::endl << std::endl;
    }

	return 0;
}

int firstInFirstOut(int pageFrameSize, std::string& referenceString)
{
	int numPageFaults = 0;

	//Index to place the pageNumber at
	int firstInIndex = 0;

	//Make a vector to hold the complete pageFrame and init the values to -1
	std::vector<int> pages(pageFrameSize, -1);

	for (char i : referenceString)
	{
		//Get numerical value of the char
		int pageNumber = i - '0';
		if(!isInPageBuffer(pages, pageNumber))
		{
			//Place the page at the spot to replace
			pages[firstInIndex] = pageNumber;
			numPageFaults++;
			//Makes sure we wrap around so 0..pagesize then back to 0
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
				auto iterator = std::find(pages.begin(), pages.end(), pageToRemove);

				// Change that number to the current page being added
				pages[std::distance(pages.begin(), iterator)] = pageNumber;
			}

			leastRecentlyUsed.push_back(pageNumber);
			numPageFaults++;
			
		}
		// The number is in pages so lets modify it to be recent in the vector 
		else
		{
			auto iterator = std::find(leastRecentlyUsed.begin(), leastRecentlyUsed.end(), pageNumber);
			
			if(iterator != leastRecentlyUsed.end())
			{
				// Erase the one in the list already
				leastRecentlyUsed.erase(iterator);
			}

			// Add it to the back to simulate it being recently used
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
			// Current page is not in the buffer but the page vector is full
			else
			{
				std::unordered_map<char, int> currentPages;

				// Add the pages to the map so we know what we need
				for (int page : pages)
				{
					currentPages.insert(std::make_pair(page, 1));
				}

				int j = i + 1;
				int currentPageNumber = pageNumber;
				// Loop until we find the one with the longest period of time until it appears
				while(j < referenceString.length() && !hasOnePageLeft(currentPages))
				{
					pageNumber = referenceString[j] - '0';
					j++;
					
					if (currentPages.find(static_cast<char>(pageNumber)) != currentPages.end())
					{
						if (currentPages[pageNumber] > 0)
						{
							currentPages[pageNumber]--;
						}
					}
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
				auto iterator = std::find(pages.begin(), pages.end(), pageToRemove);

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

void printPages(std::vector<int>& buffer)
{
    std::cout << "\n{ ";

    unsigned long size = buffer.size();

    for(int i = 0; i < size; i++)
    {
        if(i < size - 1)
        {
            std::cout << buffer[i] << ", ";
        }
        else
        {
            std::cout << buffer[i];
        }
    }

    std::cout << " }";
}

std::string generateRandomPageString()
{
	std::random_device randomDevice;  //Will be used to obtain a seed for the random number engine
	std::mt19937 generator(randomDevice()); //Standard mersenne_twister_engine seeded with randomDevice()
	std::uniform_int_distribution<> dis(0, 7);

	std::string referenceString;

	for (int i = 0; i < 30; i++)
	{
		referenceString += std::to_string(dis(generator)); //generate a number and add it to the string
	}

	return referenceString;
}


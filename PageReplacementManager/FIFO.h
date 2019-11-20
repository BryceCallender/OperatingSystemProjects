#pragma once
#include <ostream>
#include <iostream>
#include <vector>

class FIFO
{
public:
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

			//Check if the number is in the page list
			if (!isInPageBuffer(pages, pageNumber))
			{
				//Place the page at the spot to replace
				pages[firstInIndex] = pageNumber;
				numPageFaults++;
				//Makes sure we wrap around so 012 and then back to 0 for example
				firstInIndex = (firstInIndex + 1) % pageFrameSize;

				//Print the pages and show it was a page fault caused by the page
				printPages(pages);
				std::cout << " Page fault caused by: " << pageNumber << std::endl;
			}
			else
			{
				//Was in the list so a page hit!
				printPages(pages);
				std::cout << " Page hit!" << std::endl;
			}
		}

		return numPageFaults;
	}

	//Outputs the current page frame contents
	void printPages(std::vector<int>& buffer)
	{
		std::cout << "Current Page Frame: ";
		std::cout << "{ ";

		unsigned long size = buffer.size();

		for (int i = 0; i < size; i++)
		{
			if (i < size - 1)
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

	//Checks to see if the pageNumber is in the page frame
	bool isInPageBuffer(std::vector<int>& buffer, int pageNumber)
	{
		for (int element : buffer)
		{
			if (element == pageNumber)
			{
				return true;
			}
		}
		return false;
	}
};

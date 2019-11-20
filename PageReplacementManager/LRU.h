#pragma once
#include <vector>
#include <iostream>


class LRU
{
public:
	int leastRecentlyUsed(int pageFrameSize, std::string& referenceString)
	{
		int numPageFaults = 0;

		//Hold the pageFrame of pages with initial values of -1 which mean open slot
		std::vector<int> pages(pageFrameSize, -1);

		//Store the pages in a vector to find the least recently used at the front
		std::vector<int> leastRecentlyUsed;

		//Where to place the page when there is nothing in the frame
		int placeIndex = 0;

		for (char i : referenceString)
		{
			//Get numerical value of the char
			int pageNumber = i - '0';
			// If the number is not in pages then add it and that is a page fault
			if (!isInPageBuffer(pages, pageNumber))
			{
				// If the vector is not full yet
				if (!isPageVectorFull(pages))
				{
					// Place the number
					pages[placeIndex] = pageNumber;
					placeIndex++;

					//Page fault and output what caused it
					printPages(pages);
					std::cout << " Page fault caused by: " << pageNumber << std::endl;
				}
				else
				{
					// The least recent item is always going to be at the front
					int pageToRemove = leastRecentlyUsed.front();

					//Get rid of the front of the LRU to simulate taking it out
					leastRecentlyUsed.erase(leastRecentlyUsed.begin());

					// Find the page that we removed from the LRU and find out where it is in the page frame
					auto iterator = std::find(pages.begin(), pages.end(), pageToRemove);

					//Print out the page that we will be moving as well as the page frame
					printPages(pages);
					std::cout << " LRU page was: " << pageToRemove << std::endl;

					// Change that location that had the page we removed to contain the new number
					pages[std::distance(pages.begin(), iterator)] = pageNumber;
				}

				//Push the number to the LRU back meaning it was used recently
				leastRecentlyUsed.push_back(pageNumber);
				numPageFaults++;

			}
			// The number is in pages so lets modify it to be recent in the vector 
			else
			{
				//Find the pageNumber in the LRU
				auto iterator = std::find(leastRecentlyUsed.begin(), leastRecentlyUsed.end(), pageNumber);

				//If the number was found
				if (iterator != leastRecentlyUsed.end())
				{
					//Erase the one in the list already
					leastRecentlyUsed.erase(iterator);
				}

				//Add it to the back to simulate it being recently used
				leastRecentlyUsed.push_back(pageNumber);

				//Page hit!
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

	//Checks to see if the page frame is full yet
	bool isPageVectorFull(std::vector<int>& buffer)
	{
		for (int element : buffer)
		{
			if (element == -1)
			{
				return false;
			}
		}
		return true;
	}
};

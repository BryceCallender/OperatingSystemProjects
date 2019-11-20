#pragma once
#include <unordered_map>
#include <iostream>


class Optimal
{
public:
	int optimalAlgorithm(int pageFrameSize, std::string& referenceString)
	{
		int numPageFaults = 0;

		//Vector to store the pages with initial value of -1 meaning open slot
		std::vector<int> pages(pageFrameSize, -1);

		//Where to place if the frame hasn't been filled yet
		int placeIndex = 0;

		for (int i = 0; i < referenceString.length(); i++)
		{
			//Get the page number
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

					//Print out the page number that faulted and show the frame
					printPages(pages);
					std::cout << " Page fault caused by: " << pageNumber << std::endl;
				}
				// Current page is not in the buffer and the page vector is full
				else
				{
					//Hold the current pages to look for
					std::unordered_map<char, int> currentPages;

					// Add the pages to the map so we know what we need with a default value of 1 to mean its not used yet
					for (int page : pages)
					{
						currentPages.insert(std::make_pair(page, 1));
					}

					//Checking everything after where we are in the reference string
					int j = i + 1;

					//Cache the number we are at for later use
					int currentPageNumber = pageNumber;

					// Loop until we find the one with the longest period of time until it appears (will have a 1 in the map value)
					while (j < referenceString.length() && !hasOnePageLeft(currentPages))
					{
						//Get page number
						pageNumber = referenceString[j] - '0';
						//Go to next number in string
						j++;

						//If the number was found in the map
						if (currentPages.find(static_cast<char>(pageNumber)) != currentPages.end())
						{
							//If it was found decrement the variable if its not 0 already
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
						//If number has a 1 that means it was not found in the future or it was last one to be found
						if (pair.second == 1)
						{
							pageToRemove = pair.first;
						}
					}

					// Find where the page to remove is in the page frame
					auto iterator = std::find(pages.begin(), pages.end(), pageToRemove);

					//Print the number to remove and the current page frame
					printPages(pages);
					std::cout << " Optimal page to remove: " << pageToRemove << std::endl;

					// Change the location where the page to remove was with the new value that we cached earlier
					pages[std::distance(pages.begin(), iterator)] = currentPageNumber;

				}

				numPageFaults++;
			}
			else
			{
				//We had a page hit so show the page frame
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


	//Checks to see if the map has one element left in it (going to be the one to remove)
	bool hasOnePageLeft(std::unordered_map<char, int>& buffer)
	{
		int numOnes = 0;
		for (auto pair : buffer)
		{
			if (pair.second == 1)
			{
				numOnes++;
			}
		}

		return numOnes == 1;
	}

	
};

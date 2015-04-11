#include <iostream>
#include <string.h>
#include "Quash.h"

using namespace std;

int main(int argc, char *argv[])
{
	Quash *quash = new Quash();
	std::cout << "program start\n";

	while(1)
	{
		// std::cout << "loop start\n";

		char buffer[256];
		std::cin.getline(buffer, 256);
		string input(buffer);

		//terminate
		if(cin.eof())
		{
			std::cout << "terminate\n";
			break;
		}

		//insert
		if(input.compare(0,6,"insert") == 0)
		{
			// std::cout << "input is insert\n";
			strtok(buffer, " ");
		  int numToInsert = (int)atoi(strtok(NULL,"\n"));	

			bool inserted = quash->insertElement(numToInsert);
			if(inserted == true) 
				cout << "item successfully inserted\n";
                                //quash->printCount(numToInsert);	

		}

		//lookup
		else if(input.compare(0,6,"lookup") == 0)
		{
			// std::cout << "input is lookup\n";
			strtok(buffer, " ");
		  int numToLookup = (int)atoi(strtok(NULL,"\n"));		
		  //	std::cout << "num to lookup is " << numToLookup << "\n";
			bool numFound = quash->lookupElement(numToLookup);
			if(numFound == true)
				cout << "item found\n";
			else
				cout << "item not found\n";			
		}

		//print
		else if(input.compare("print") == 0)
		{
			// std::cout << "input is print\n";
			quash->printHeap();
		}

		//deleteMin
		else if(input.compare("deleteMin") == 0)
		{
			// std::cout << "input is deleteMin\n";
			if (quash->isMin())
			{
				cout << "min item " << quash->getMin() << "successfully deleted\n";
				quash->deleteMin();
			}
			else
				cout << "min item not present since table is empty\n";
		}

		//delete 
		else if(input.compare(0,7,"delete ") == 0)
		{
			// std::cout << "input is delete\n";
			strtok(buffer, " ");
			int numToDelete = (int)atoi(strtok(NULL,"\n"));
			bool deleted = quash->deleteElement(numToDelete);
			if(deleted == true)
				cout << "item successfully deleted\n";
			else
				cout << "item not present in the table\n";
		}
		
		//other inputs - make user reenter input
		else
		{
			std::cout << "invalid input\n";
		}

	}
	return 0;
    }


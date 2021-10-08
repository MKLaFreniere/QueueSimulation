//Mark LaFreniere
//Creation: 11/25/2020
//Modified: 11/25/2020
//Purpose: To generate test data
#include<fstream>
#include<ctime>

using namespace std;

struct job {
	int arrival;
	int processing;
	char jobType;
};

struct node {
	job unit;
	node* next;
};

void Insert(job, node**);
node* GenerateData();
void PrintLink(node*);

int main()
{
	srand(time(NULL));		// initialize random seed

	node* list = GenerateData();

	PrintLink(list);

	return 0;
}

void Insert(job item, node** head)
{
	node* currPtr, * prevPtr, * insertItem = new node;
	insertItem->unit = item;
	insertItem->next = nullptr;
	currPtr = (*head);
	prevPtr = nullptr;

	while ((currPtr != nullptr) && (item.arrival > currPtr->unit.arrival))		// Iterate to proper position in list
	{
		prevPtr = currPtr;
		currPtr = currPtr->next;
	}

	if ((prevPtr == nullptr) && (currPtr == nullptr))	//create new
	{
		(*head) = insertItem;
	}
	if (prevPtr == nullptr)		//Add to beginning
	{
		insertItem->next = currPtr;
		(*head) = insertItem;
	}
	else if (currPtr != nullptr)	//Add in between
	{
		insertItem->next = currPtr;
		prevPtr->next = insertItem;
	}
	else							//Add to end
	{
		prevPtr->next = insertItem;
	}
}

node* GenerateData()
{
	job input;
	node* list = nullptr;
	int cumulativeTime = 0;

	for (int i = 0; i < 2500; i++)			// Job A
	{
		input.jobType = 'A';
		input.arrival = 4 + rand() % 3;
		input.processing = 1 + rand() % 5;

		cumulativeTime += input.arrival;		// add arrival time to cumulative time
		input.arrival = cumulativeTime;

		Insert(input, &list);
	}

	cumulativeTime = 0;							// reset cumulative time

	for (int i = 0; i < 1200; i++)			// Job B
	{
		input.jobType = 'B';
		input.arrival = 9 + rand() % 3;
		input.processing = 6 + rand() % 5;

		cumulativeTime += input.arrival;		// add arrival time to cumulative time
		input.arrival = cumulativeTime;

		Insert(input, &list);
	}

	cumulativeTime = 0;							// reset cumulative time

	for (int i = 0; i < 450; i++)			// Job C
	{
		input.jobType = 'C';
		input.arrival = 24 + rand() % 3;
		input.processing = 9 + rand() % 5;

		cumulativeTime += input.arrival;		// add arrival time to cumulative time
		input.arrival = cumulativeTime;

		Insert(input, &list);
	}

	return list;
}

void PrintLink(node* list)
{
	ofstream ofs("JobData.txt");

	while (list)
	{
		ofs << list->unit.jobType << ' ' << list->unit.arrival << ' ' << list->unit.processing << endl;
		list = list->next;
	}

	ofs.close();
}
//Mark LaFreniere
//Creation 12/1/2020
//Modified 12/4/2020
//Queue Methods
#include"ProcessQueue.h"
#include<iostream>
#include<limits>

using namespace std;


ProcessQueue::~ProcessQueue()
{
	delete waitlist;
	waitlist = nullptr;
}

bool ProcessQueue::IsEmpty()
{
	if (waitlist == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ProcessQueue::Enqueue(const job newJob)
{
	node * currPtr, * prevPtr, * insertItem = new node;

	insertItem->currJob = newJob;
	insertItem->next = nullptr;
	currPtr = waitlist;
	prevPtr = nullptr;
	
	while (currPtr != nullptr)		// Move to end of queue
	{
		prevPtr = currPtr;
		currPtr = currPtr->next;
	}
	
	if (prevPtr == nullptr)			// Add first new job to queue
	{
		waitlist = insertItem;
	}
	else							// Add to end of queue
	{
		prevPtr->next = insertItem;
	}
}

job ProcessQueue::Dequeue()
{
	bool alreadyEmpty = IsEmpty();

	if (alreadyEmpty == true)			// Catches process trying to dequeue an empty queue (try/catch in proper main or other function)
	{
		throw alreadyEmpty;
	}

	node* currPtr = new node;
	job leavingJob;

	leavingJob = waitlist->currJob;		// Job being dequeued is head of queue

	currPtr = waitlist;					// Head is changed to next item in queue
	waitlist = currPtr->next;
	
	delete currPtr;						// Original head is deleted when leaving queue
	currPtr = nullptr;

	return leavingJob;
}

int ProcessQueue::Size()
{
	node* currPtr = new node;
	int counter = 1;
	currPtr = waitlist;

	if (currPtr == nullptr)
	{
		return 0;
	}

	while (currPtr != nullptr)
	{
		currPtr = currPtr->next;
		counter++;
	}

	return counter;
}

int ProcessQueue::GetArrivalTime()
{
	if (waitlist == nullptr)
	{							// Since 'time' must be greater or equal than the arrival time for
		return INT_MAX;			// a job to be dequeued, when no jobs are in the list it is set 
	}							// to max value. This prevents false triggers of dequeueing an idle processor
	else
	{
		return waitlist->currJob.arrivalTime;
	}
	
}

int ProcessQueue::GetTotalProcessTime()
{
	node* currPtr = new node;
	int total = 0;

	currPtr = waitlist;

	if (waitlist == nullptr)
	{
		return 0;
	}
	else
	{
		while (currPtr != nullptr)
		{
			total += currPtr->currJob.processingTime;
			currPtr = currPtr->next;
		}

		return total;
	}
}
//Mark LaFreniere
//Creation 12/1/2020
//Modified 12/4/2020
//Project 2
#include<fstream>
#include<iostream>
#include<iomanip>
#include"ProcessQueue.h"
using namespace std;

const int INITIAL_METRIC_TIME = 500;
const int FINAL_METRIC_TIME = 10000;
const int INITIAL_TIME = 1;
const int TOTAL_POSSIBLE_PROCESSORS = 8;

 void ReadFile(ProcessQueue&);
 void InitializeProcessors(bool[]);
 void InsertMetricSizeList(int, avgNode**);
 float CalculateAverage(avgNode*);
 int CalculateLargest(avgNode*);
 float CalculatePercentTimeUse(int, int);

int main()
{
	int time = INITIAL_TIME;
	int runningProcessors = -1;
	ofstream ofsLog("Log.txt");
	ofstream ofsMetrics("Metrics.txt");
	ProcessQueue separateArrivalList;
	ProcessQueue jobWaitList;
	avgNode* jobQueueValues = nullptr;
	float averageQueueSize;
	int largestQueueSize;
	int numProcessorsInUse = 0;
	int totalJobsCompleted = 0;
	int totalCpuProcessingTime = 0;
	int idleCpuProcessingTime = 0;
	int totalAJobsArrived = 0;
	int totalBJobsArrived = 0;
	int totalCJobsArrived = 0;
	int totalTimeJobsInQueue = 0;
	float timePercentInUse;
	int maxPossibleJobsCompleted = 0;
	bool processor[TOTAL_POSSIBLE_PROCESSORS];
	job jobInProcessor[TOTAL_POSSIBLE_PROCESSORS];
	int currProcessTime[TOTAL_POSSIBLE_PROCESSORS];
	bool allProcessorsInUse = false;
	float percComplete;

	ReadFile(separateArrivalList);		// Put file data into a separate queue for ease of access

	InitializeProcessors(processor);	// Set all processors to true, which means free

	while (!(runningProcessors >= 1 && runningProcessors <= TOTAL_POSSIBLE_PROCESSORS))		// User choses how many processors to run
	{
		cout << "How many processors will run? (1-" << TOTAL_POSSIBLE_PROCESSORS << "): ";
		cin >> runningProcessors;
	}
	
	cout << endl;
	
	while (time <= FINAL_METRIC_TIME)		// Beginning of time unit
	{
																
															// Start of Processors ----------------------------
		for (int i = 0; i < runningProcessors; i++)				
		{
			if (processor[i] == true)				// If the processor is free, it is true
			{
				if ((time >= separateArrivalList.GetArrivalTime()) || (time >= jobWaitList.GetArrivalTime()))	// If there is a job to give at its arrival time or in queue
				{
					try {
						if (jobWaitList.IsEmpty() == true)		// If the queue is empty add from the arrivals list, else add from the queue
						{
							jobInProcessor[i] = separateArrivalList.Dequeue();

						}
						else
						{
							jobInProcessor[i] = jobWaitList.Dequeue();

						}
					}
					catch(bool alreadyEmpty)		// Catches possible error for dequeueing an empty queue
					{
						ofsMetrics << "Error: Tried to dequeue empty queue." << endl << "Aborted..." << endl;
					}
					

					currProcessTime[i] = 0;			// Set the processing time to 0
					processor[i] = false;			// Change the processor to 'not free'
					numProcessorsInUse++;			// Increment the amount of processors currently in use

					switch (jobInProcessor[i].type)		// Increment the amount of jobs arrived at processors by type
					{
					case 'A':
						totalAJobsArrived++;
						break;
					case 'B':
						totalBJobsArrived++;
						break;
					case 'C':
						totalCJobsArrived++;
						break;
					}

					ofsLog << "Time " << time << ":  Processor " << i + 1 << " : Job " << jobInProcessor[i].jobNum
						<< " : Type " << jobInProcessor[i].type << "-" << jobInProcessor[i].typeNum << ": Arrived" << endl;	// Input data into log
				}
				else		// If there is no job available for the free processor
				{
					idleCpuProcessingTime++;

					ofsLog << "Time " << time << ":  Processor " << i+1 << " : Idle" << endl;
				}

			}
			else if (processor[i] == false)			// If processor is currently in use
			{
				currProcessTime[i]++;			// Increase the time processor has been processing with time
				totalCpuProcessingTime++;		// Increase time of total processing

				if (currProcessTime[i] >= jobInProcessor[i].processingTime)	// When a job finishes processing
				{
					processor[i] = true;		// Set processor to free
					numProcessorsInUse--;		// Decrement the amount of processors in use
					totalJobsCompleted++;		// At to tally of jobs done
					currProcessTime[i] = 0;		// set the processing time within processor back to 0

					ofsLog << "Time " << time << ":  Processor " << i + 1 << " : Job " << jobInProcessor[i].jobNum 
						<< " : Type " << jobInProcessor[i].type << "-" << jobInProcessor[i].typeNum << ": Finished" << endl;	// Log info
				}
				else			// Else log the percentage a job is complete
				{
					percComplete = jobInProcessor[i].processingTime;		// Calculates the percentage that a job is complete
					percComplete = currProcessTime[i] / percComplete;
					percComplete *= 100;

					ofsLog << "Time " << time << ":  Processor " << i + 1 <<  " : Job " << jobInProcessor[i].jobNum
						<< " : Type " << jobInProcessor[i].type << "-" << jobInProcessor[i].typeNum << ": " << setprecision(2) << percComplete << "% Complete" << endl;
				}
			}
		}													// End of Processors -----------------------------------
		
															// Start of Queue --------------------------------------

		for (int i = 0; i < runningProcessors; i++)			// Checks if all processors are full
		{
			if (processor[i] == true)
			{
				allProcessorsInUse = false;
				break;
			}
			else
			{
				allProcessorsInUse = true;
			}
		}

		if ((allProcessorsInUse == true) && (time >= separateArrivalList.GetArrivalTime()))		// Adds new job to queue if all processors are full
		{
			jobWaitList.Enqueue(separateArrivalList.Dequeue());
		}

		if (jobWaitList.IsEmpty() == false)			// Adds to total time a job is in queue if the queue is not empty
		{
			totalTimeJobsInQueue++;
			ofsLog << "Time " << time << ":  Queue : " << jobWaitList.Size() << " job(s)" << endl;
		}
		else										// Writes that the queue is empty into a log
		{
			ofsLog << "Time " << time << ":  Queue : Empty" << endl;
		}
																// End of Queue ---------------------------------------

																// Start of Metrics -----------------------------------


		InsertMetricSizeList(jobWaitList.Size(), &jobQueueValues);			// Insert queue size into list used to calculate metrics

		averageQueueSize = CalculateAverage(jobQueueValues);			// Calculate average queue size

		largestQueueSize = CalculateLargest(jobQueueValues);			// Caluclate largest amount of items in queue

		timePercentInUse = CalculatePercentTimeUse(idleCpuProcessingTime, totalCpuProcessingTime); // Calculate the percentage of time that cpus are in use

		if ((time == INITIAL_METRIC_TIME) || (time == FINAL_METRIC_TIME))				// Write all metric data into Metrics.txt at designated times
		{
			ofsMetrics << "Metrics at time: " << time << " -- Number of processors: " << runningProcessors << endl << endl
				<< "  Num processors currently in use: " << numProcessorsInUse << endl
				<< "  Current queue size: " << jobWaitList.Size() << endl
				<< "  Overall average queue size: " << averageQueueSize << endl
				<< "  Maximum jobs in queue: " << largestQueueSize << endl
				<< "  Total time jobs in queue: " << totalTimeJobsInQueue << " time units" << endl
				<< "  Total number of jobs A arrived: " << totalAJobsArrived << endl
				<< "  Total number of jobs B arrived: " << totalBJobsArrived << endl
				<< "  Total number of jobs C arrived: " << totalCJobsArrived << endl
				<< "  Total jobs completed: " << totalJobsCompleted << endl
				<< "  Total time CPU(s) were processing: " << totalCpuProcessingTime << " time units" << endl
				<< "  Total time CPU(s) were idle: " << idleCpuProcessingTime << " time units: " << endl
				<< "  Percentage of time processors in use: " << timePercentInUse << "%" << endl 
				<< endl;
		}
																// End of Metrics ------------------------------------

		time++; // End of one time unit, increment time
	}

	ofsLog.close();
	ofsMetrics.close();
	return 0;
}

void ReadFile(ProcessQueue& list)
{
	//ProcessQueue list;
	ifstream ifs("JobData.txt");
	job data;
	int overallJobNumber = 1;
	int jobANum = 1;
	int jobBNum = 1;
	int jobCNum = 1;

	while (!ifs.eof())		// While the file is not empty,
	{
		ifs >> data.type >> data.arrivalTime >> data.processingTime;	// Input line of data into temporary variable

		data.jobNum = overallJobNumber;
		
		switch (data.type) {
		case 'A':
			data.typeNum = jobANum;
			jobANum++;
			break;
		case 'B':
			data.typeNum = jobBNum;
			jobBNum++;
			break;
		case 'C':
			data.typeNum = jobCNum;
			jobCNum++;
			break;
		}

		list.Enqueue(data);		// Enqueue temporary data into arrival queue
		overallJobNumber++;
	}

	ifs.close();
	
}

void InitializeProcessors(bool processors[])
{
	for (int i = 0; i < TOTAL_POSSIBLE_PROCESSORS; i++)
	{
		processors[i] = true;
	}
}

void InsertMetricSizeList(int item, avgNode** head)
{
	avgNode* currPtr, * prevPtr, * insertItem = new avgNode;
	
	insertItem->queueSize = item;
	insertItem->next = nullptr;
	currPtr = (*head);
	prevPtr = nullptr;

	while (currPtr != nullptr)		// Move pointers up the list
	{
		prevPtr = currPtr;
		currPtr = currPtr->next;
	}

	if (prevPtr == nullptr)			// Create new list
	{
		(*head) = insertItem;
	}
	else							// Add to end of list
	{
		prevPtr->next = insertItem;
	}
	
	
}

float CalculateAverage(avgNode* head)
{
	avgNode* currPtr = new avgNode;
	int size = 0;
	float total = 0;

	currPtr = head;

	while (currPtr != nullptr)			// While not at the end of the list,
	{
		total += currPtr->queueSize;	// Find out total sizes the queue has been at throughout time
		size++;							// Find out size of avgNode list
		currPtr = currPtr->next;
	}
	
	return total / size;
}

int CalculateLargest(avgNode* head)
{
	avgNode* currPtr = new avgNode;
	int largest = 0;
	currPtr = head;

	while (currPtr != nullptr)			// While not at end of list
	{
		if (largest < currPtr->queueSize)	// If size in list is larger, make largest equal it
		{
			largest = currPtr->queueSize;
		}

		currPtr = currPtr->next;
	}

	return largest;
}

float CalculatePercentTimeUse(int idleTime, int processingTime)
{
	float a = processingTime;		// Calculate percentage based on the total time 
	float b = a + idleTime;			// that the processors have processed and the 
	float c = a / b;				// total time they have been idle

	return c * 100;
}
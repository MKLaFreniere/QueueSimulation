//Mark LaFreniere
//Creation 12/1/2020
//Modified 12/1/2020
//Project 2
#include<fstream>
#include<iostream>
#include<iomanip>
#include"ProcessQueue.h"
using namespace std;

const int INITIAL_METRIC_TIME = 500;
const int FINAL_METRIC_TIME = 10000;
const int INITIAL_TIME = 1;

 void ReadFile(ProcessQueue&);
 void InsertAverageList(int, avgNode**);
 float CalculateAverage(avgNode*);
 int CalculateLargest(avgNode*);

int main()
{
	/*
	*   NOTES:
	* 
	* Added all data from file to another separate queue for ease of access.
	*
	* Each processor is essentially 2 if statements dictated by a bool value.
	*
	* Everything is in a while loop -- while(time <= FINAL_TIME_METRIC)
	*
	* If all processors are false, item is added into jobWaitList
	*
	* Calculated all metric data after the processors in each time unit
	* 
	* Take note that the maximum amount of jobs that can be completed in 10000 time units is 3403
	* 
	* 
	* 
	*   THINGS TO DO:
	* 
	*  Clean up the code, because it is very messy
	*			EX: maybe throw processor specific values into an array with size 8
	*				This could cut down on the amount of variables
	* 
	*  Check more to see if it functions properly, so far metrics look reasonable
	* 
	*  Add a function to calculate the Average time in queue
	* 
	*  Metrics need to be written into Metrics.txt, but we will do this last so we can always view it quickly
	* 
	*  More relavent data can be written into the log.txt
	* 
	*  Add more comments to explain how the program works, I can do this
	*/

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
	float averageTimeJobsInQueue;

	// Processor 1
	bool processor1 = true;
	job jobInProcessor1;
	int currProcessTime1;

	// Processor 2
	bool processor2 = true;
	job jobInProcessor2;
	int currProcessTime2;

	// Processor 3
	bool processor3 = true;
	job jobInProcessor3;
	int currProcessTime3;

	// Processor 4
	bool processor4 = true;
	job jobInProcessor4;
	int currProcessTime4;

	// Processor 5
	bool processor5 = true;
	job jobInProcessor5;
	int currProcessTime5;

	// Processor 6
	bool processor6 = true;
	job jobInProcessor6;
	int currProcessTime6;

	// Processor 7
	bool processor7 = true;
	job jobInProcessor7;
	int currProcessTime7;

	// Processor 8
	bool processor8 = true;
	job jobInProcessor8;
	int currProcessTime8;



	ReadFile(separateArrivalList);

	while (!(runningProcessors > 0 && runningProcessors < 9))
	{
		cout << "How many processors will run? (1-8): ";
		cin >> runningProcessors;
	}
	
	cout << endl;
	
	while (time <= FINAL_METRIC_TIME)
	{
		switch (runningProcessors)							// Determimes how many processors will run at once
		{
		case 8:

			////////////////////////////////////////////////////////////////////////////////////////////////////////// 

																												// Processor 8
			if (processor8 == true)
			{
				if ((time >= separateArrivalList.GetArrivalTime()) || (time >= jobWaitList.GetArrivalTime()))
				{
					if (jobWaitList.IsEmpty() == true)
					{
						jobInProcessor8 = separateArrivalList.Dequeue();

					}
					else
					{
						jobInProcessor8 = jobWaitList.Dequeue();

					}

					currProcessTime8 = 0;
					processor8 = false;
					numProcessorsInUse++;

					switch (jobInProcessor8.type)
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

					ofsLog << "Time " << time << ":   Arrival  : Job " << jobInProcessor8.jobNum << " : Type " << jobInProcessor8.type << "-" << jobInProcessor8.typeNum << " : Processor 8" << endl;
				}
				else
				{
					idleCpuProcessingTime++;

					ofsLog << "Time " << time << ":   Processor 8 - Idle" << endl;
				}

			}

			if (processor8 == false)
			{
				currProcessTime8++;
				totalCpuProcessingTime++;

				if (currProcessTime8 > jobInProcessor8.processingTime)
				{
					processor8 = true;
					numProcessorsInUse--;
					totalJobsCompleted++;
					currProcessTime8 = 0;

					ofsLog << "Time " << time << ":   Finished : Job " << jobInProcessor8.jobNum << " : Type " << jobInProcessor8.type << "-" << jobInProcessor8.typeNum << " : Processor 8" << endl;
				}
			}

		case 7:

			////////////////////////////////////////////////////////////////////////////////////////////////////////// 

																												// Processor 7
			if (processor7 == true)
			{
				if ((time >= separateArrivalList.GetArrivalTime()) || (time >= jobWaitList.GetArrivalTime()))
				{
					if (jobWaitList.IsEmpty() == true)
					{
						jobInProcessor7 = separateArrivalList.Dequeue();

					}
					else
					{
						jobInProcessor7 = jobWaitList.Dequeue();

					}

					currProcessTime7 = 0;
					processor7 = false;
					numProcessorsInUse++;

					switch (jobInProcessor7.type)
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

					ofsLog << "Time " << time << ":   Arrival  : Job " << jobInProcessor7.jobNum << " : Type " << jobInProcessor7.type << "-" << jobInProcessor7.typeNum << " : Processor 7" << endl;
				}
				else
				{
					idleCpuProcessingTime++;

					ofsLog << "Time " << time << ":   Processor 7 - Idle" << endl;
				}

			}

			if (processor7 == false)
			{
				currProcessTime7++;
				totalCpuProcessingTime++;

				if (currProcessTime7 > jobInProcessor7.processingTime)
				{
					processor7 = true;
					numProcessorsInUse--;
					totalJobsCompleted++;
					currProcessTime7 = 0;

					ofsLog << "Time " << time << ":   Finished : Job " << jobInProcessor7.jobNum << " : Type " << jobInProcessor7.type << "-" << jobInProcessor7.typeNum << " : Processor 7" << endl;
				}
			}

		case 6:

			////////////////////////////////////////////////////////////////////////////////////////////////////////// 

																												// Processor 6
			if (processor6 == true)
			{
				if ((time >= separateArrivalList.GetArrivalTime()) || (time >= jobWaitList.GetArrivalTime()))
				{
					if (jobWaitList.IsEmpty() == true)
					{
						jobInProcessor6 = separateArrivalList.Dequeue();

					}
					else
					{
						jobInProcessor6 = jobWaitList.Dequeue();

					}

					currProcessTime6 = 0;
					processor6 = false;
					numProcessorsInUse++;

					switch (jobInProcessor6.type)
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

					ofsLog << "Time " << time << ":   Arrival  : Job " << jobInProcessor6.jobNum << " : Type " << jobInProcessor6.type << "-" << jobInProcessor6.typeNum << " : Processor 6" << endl;
				}
				else
				{
					idleCpuProcessingTime++;

					ofsLog << "Time " << time << ":   Processor 6 - Idle" << endl;
				}

			}

			if (processor6 == false)
			{
				currProcessTime6++;
				totalCpuProcessingTime++;

				if (currProcessTime6 > jobInProcessor6.processingTime)
				{
					processor6 = true;
					numProcessorsInUse--;
					totalJobsCompleted++;
					currProcessTime6 = 0;

					ofsLog << "Time " << time << ":   Finished : Job " << jobInProcessor6.jobNum << " : Type " << jobInProcessor6.type << "-" << jobInProcessor6.typeNum << " : Processor 6" << endl;
				}
			}

		case 5:

			////////////////////////////////////////////////////////////////////////////////////////////////////////// 

																												// Processor 5
			if (processor5 == true)
			{
				if ((time >= separateArrivalList.GetArrivalTime()) || (time >= jobWaitList.GetArrivalTime()))
				{
					if (jobWaitList.IsEmpty() == true)
					{
						jobInProcessor5 = separateArrivalList.Dequeue();

					}
					else
					{
						jobInProcessor5 = jobWaitList.Dequeue();

					}

					currProcessTime5 = 0;
					processor5 = false;
					numProcessorsInUse++;

					switch (jobInProcessor5.type)
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

					ofsLog << "Time " << time << ":   Arrival  : Job " << jobInProcessor5.jobNum << " : Type " << jobInProcessor5.type << "-" << jobInProcessor5.typeNum << " : Processor 5" << endl;
				}
				else
				{
					idleCpuProcessingTime++;

					ofsLog << "Time " << time << ":   Processor 5 - Idle" << endl;
				}

			}

			if (processor5 == false)
			{
				currProcessTime5++;
				totalCpuProcessingTime++;

				if (currProcessTime5 > jobInProcessor5.processingTime)
				{
					processor5 = true;
					numProcessorsInUse--;
					totalJobsCompleted++;
					currProcessTime5 = 0;

					ofsLog << "Time " << time << ":   Finished : Job " << jobInProcessor5.jobNum << " : Type " << jobInProcessor5.type << "-" << jobInProcessor5.typeNum << " : Processor 5" << endl;
				}
			}

		case 4:

			////////////////////////////////////////////////////////////////////////////////////////////////////////// 

																												// Processor 4
			if (processor4 == true)
			{
				if ((time >= separateArrivalList.GetArrivalTime()) || (time >= jobWaitList.GetArrivalTime()))
				{
					if (jobWaitList.IsEmpty() == true)
					{
						jobInProcessor4 = separateArrivalList.Dequeue();

					}
					else
					{
						jobInProcessor4 = jobWaitList.Dequeue();

					}

					currProcessTime4 = 0;
					processor4 = false;
					numProcessorsInUse++;

					switch (jobInProcessor4.type)
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

					ofsLog << "Time " << time << ":   Arrival  : Job " << jobInProcessor4.jobNum << " : Type " << jobInProcessor4.type << "-" << jobInProcessor4.typeNum << " : Processor 4" << endl;
				}
				else
				{
					idleCpuProcessingTime++;

					ofsLog << "Time " << time << ":   Processor 4 - Idle" << endl;
				}

			}

			if (processor4 == false)
			{
				currProcessTime4++;
				totalCpuProcessingTime++;

				if (currProcessTime4 > jobInProcessor4.processingTime)
				{
					processor4 = true;
					numProcessorsInUse--;
					totalJobsCompleted++;
					currProcessTime4 = 0;

					ofsLog << "Time " << time << ":   Finished : Job " << jobInProcessor4.jobNum << " : Type " << jobInProcessor4.type << "-" << jobInProcessor4.typeNum << " : Processor 4" << endl;
				}
			}

		case 3:

			////////////////////////////////////////////////////////////////////////////////////////////////////////// 

																												// Processor 3
			if (processor3 == true)
			{
				if ((time >= separateArrivalList.GetArrivalTime()) || (time >= jobWaitList.GetArrivalTime()))
				{
					if (jobWaitList.IsEmpty() == true)
					{
						jobInProcessor3 = separateArrivalList.Dequeue();

					}
					else
					{
						jobInProcessor3 = jobWaitList.Dequeue();

					}

					currProcessTime3 = 0;
					processor3 = false;
					numProcessorsInUse++;

					switch (jobInProcessor3.type)
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

					ofsLog << "Time " << time << ":   Arrival  : Job " << jobInProcessor3.jobNum << " : Type " << jobInProcessor3.type << "-" << jobInProcessor3.typeNum << " : Processor 3" << endl;
				}
				else
				{
					idleCpuProcessingTime++;

					ofsLog << "Time " << time << ":   Processor 3 - Idle" << endl;
				}

			}

			if (processor3 == false)
			{
				currProcessTime3++;
				totalCpuProcessingTime++;

				if (currProcessTime3 > jobInProcessor3.processingTime)
				{
					processor3 = true;
					numProcessorsInUse--;
					totalJobsCompleted++;
					currProcessTime3 = 0;

					ofsLog << "Time " << time << ":   Finished : Job " << jobInProcessor3.jobNum << " : Type " << jobInProcessor3.type << "-" << jobInProcessor3.typeNum << " : Processor 3" << endl;
				}
			}

		case 2:

			////////////////////////////////////////////////////////////////////////////////////////////////////////// 

																												// Processor 2
			if (processor2 == true)																				
			{
				if ((time >= separateArrivalList.GetArrivalTime()) || (time >= jobWaitList.GetArrivalTime()))
				{
					if (jobWaitList.IsEmpty() == true)
					{
						jobInProcessor2 = separateArrivalList.Dequeue();

					}
					else
					{
						jobInProcessor2 = jobWaitList.Dequeue();

					}

					currProcessTime2 = 0;
					processor2 = false;
					numProcessorsInUse++;

					switch (jobInProcessor2.type)
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

					ofsLog << "Time " << time << ":   Arrival  : Job " << jobInProcessor2.jobNum << " : Type " << jobInProcessor2.type << "-" << jobInProcessor2.typeNum << " : Processor 2" << endl;
				}
				else
				{
					idleCpuProcessingTime++;

					ofsLog << "Time " << time << ":   Processor 2 - Idle" << endl;
				}

			}

			if (processor2 == false)
			{
				currProcessTime2++;
				totalCpuProcessingTime++;

				if (currProcessTime2 > jobInProcessor2.processingTime)
				{
					processor2 = true;
					numProcessorsInUse--;
					totalJobsCompleted++;
					currProcessTime2 = 0;

					ofsLog << "Time " << time << ":   Finished : Job " << jobInProcessor2.jobNum << " : Type " << jobInProcessor2.type << "-" << jobInProcessor2.typeNum << " : Processor 2" << endl;
				}
			}

		case 1:

			////////////////////////////////////////////////////////////////////////////////////////////////////////// 

																												// Processor 1
			if (processor1 == true)																				
			{
				if ((time >= separateArrivalList.GetArrivalTime()) || (time >= jobWaitList.GetArrivalTime()))
				{
					if (jobWaitList.IsEmpty() == true)
					{
						jobInProcessor1 = separateArrivalList.Dequeue();

					}
					else
					{
						jobInProcessor1 = jobWaitList.Dequeue();

					}

					currProcessTime1 = 0;
					processor1 = false;
					numProcessorsInUse++;

					switch (jobInProcessor1.type)
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

					ofsLog << "Time " << time << ":   Arrival  : Job " << jobInProcessor1.jobNum << " : Type " << jobInProcessor1.type << "-" << jobInProcessor1.typeNum << " : Processor 1" << endl;
				}
				else
				{
					idleCpuProcessingTime++;

					ofsLog << "Time " << time << ":   Processor 1 - Idle" << endl;
				}

			}

			if (processor1 == false)
			{
				currProcessTime1++;
				totalCpuProcessingTime++;

				if (currProcessTime1 > jobInProcessor1.processingTime)
				{
					processor1 = true;
					numProcessorsInUse--;
					totalJobsCompleted++;
					currProcessTime1 = 0;

					ofsLog << "Time " << time << ":   Finished : Job " << jobInProcessor1.jobNum << " : Type " << jobInProcessor1.type << "-" << jobInProcessor1.typeNum << " : Processor 1" << endl;
				}
			}

		}
			
			//////////////////////////////////////////////////////////////////////////////////////////////////////////

																												//when processors are full, put into queue. Dependent on number of processors
		switch (runningProcessors)				
		{
		case 1:

			if ((processor1 == false) && (time >= separateArrivalList.GetArrivalTime()))		
			{
				jobWaitList.Enqueue(separateArrivalList.Dequeue());
			}
			break;

		case 2:

			if ((processor1 == false) && (processor2 == false) && (time >= separateArrivalList.GetArrivalTime()))
			{
				jobWaitList.Enqueue(separateArrivalList.Dequeue());
			}
			break;

		case 3:

			if ((processor1 == false) && (processor2 == false) && (processor3 == false) && (time >= separateArrivalList.GetArrivalTime()))
			{
				jobWaitList.Enqueue(separateArrivalList.Dequeue());
			}
			break;

		case 4:

			if ((processor1 == false) && (processor2 == false) && (processor3 == false) && (processor4 == false) && (time >= separateArrivalList.GetArrivalTime()))
			{
				jobWaitList.Enqueue(separateArrivalList.Dequeue());
			}
			break;

		case 5:

			if ((processor1 == false) && (processor2 == false) && (processor3 == false) && (processor4 == false) && (processor5 == false) && (time >= separateArrivalList.GetArrivalTime()))
			{
				jobWaitList.Enqueue(separateArrivalList.Dequeue());
			}
			break;

		case 6:

			if ((processor1 == false) && (processor2 == false) && (processor3 == false) && (processor4 == false) && (processor5 == false) && (processor6 == false) && (time >= separateArrivalList.GetArrivalTime()))
			{
				jobWaitList.Enqueue(separateArrivalList.Dequeue());
			}
			break;

		case 7:

			if ((processor1 == false) && (processor2 == false) && (processor3 == false) && (processor4 == false) && (processor5 == false) && (processor6 == false) && (processor7 == false) && (time >= separateArrivalList.GetArrivalTime()))
			{
				jobWaitList.Enqueue(separateArrivalList.Dequeue());
			}
			break;

		case 8:

			if ((processor1 == false) && (processor2 == false) && (processor3 == false) && (processor4 == false) && (processor5 == false) && (processor6 == false) && (processor7 == false) && (processor8 == false) && (time >= separateArrivalList.GetArrivalTime()))
			{
				jobWaitList.Enqueue(separateArrivalList.Dequeue());
			}
			break;
		}
		
			//////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		if (jobWaitList.IsEmpty() == false)			// Adds to total time a job is in queue
		{
			totalTimeJobsInQueue++;
		}
		else										// Writes that the queue is empty into a log
		{
			ofsLog << "Time " << time << ":   Queue Empty" << endl;
		}
		

		//averageTimeJobsInQueue 

		InsertAverageList(jobWaitList.Size(), &jobQueueValues);			// Insert into list used to calculate metrics

		averageQueueSize = CalculateAverage(jobQueueValues);			// Calculate average queue size

		largestQueueSize = CalculateLargest(jobQueueValues);			// Caluclate largest amount of items in queue

		if ((time == INITIAL_METRIC_TIME) || (time == FINAL_METRIC_TIME))
		{
			cout << "Metrics at time: " << time << endl << endl
				<< "  Num Processors in use: " << numProcessorsInUse << endl
				<< "  Current queue size: " << jobWaitList.Size() << endl
				<< "  Average queue size: " << averageQueueSize << endl
				<< "  Maximum jobs in queue: " << largestQueueSize << endl
				<< "  Total time jobs in queue: " << totalTimeJobsInQueue << endl
				<< "  Average time in queue:" << " Not Calculated" << endl
				<< "  Total number of jobs A arrived: " << totalAJobsArrived << endl
				<< "  Total number of jobs B arrived: " << totalBJobsArrived << endl
				<< "  Total number of jobs C arrived: " << totalCJobsArrived << endl
				<< "  Total jobs completed: " << totalJobsCompleted << endl
				<< "  Total time CPU(s) were processing: " << totalCpuProcessingTime << endl
				<< "  Total time CPU(s) were idle: " << idleCpuProcessingTime << " time units: " << endl << endl;
		}
		
		time++;
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

	while (!ifs.eof())
	{
		ifs >> data.type >> data.arrivalTime >> data.processingTime;

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

		list.Enqueue(data);
		overallJobNumber++;
	}

	ifs.close();
	
}

void InsertAverageList(int item, avgNode** head)
{
	avgNode* currPtr, * prevPtr, * insertItem = new avgNode;
	
	insertItem->queueSize = item;
	insertItem->next = nullptr;
	currPtr = (*head);
	prevPtr = nullptr;

	while (currPtr != nullptr)
	{
		prevPtr = currPtr;
		currPtr = currPtr->next;
	}

	if (prevPtr == nullptr)			//create new
	{
		(*head) = insertItem;
	}
	else
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

	while (currPtr != nullptr)
	{
		total += currPtr->queueSize;
		size++;
		currPtr = currPtr->next;
	}
	
	return total / size;
}

int CalculateLargest(avgNode* head)
{
	avgNode* currPtr = new avgNode;
	int largest = 0;
	currPtr = head;

	while (currPtr != nullptr)
	{
		if (largest < currPtr->queueSize)
		{
			largest = currPtr->queueSize;
		}

		currPtr = currPtr->next;
	}

	return largest;
}
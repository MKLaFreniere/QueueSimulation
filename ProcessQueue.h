//Mark LaFreniere
//Creation 12/1/2020
//Modified 12/4/2020
//Queue Header File

using namespace std;

#ifndef QUEUE_H
#define QUEUE_H

struct job {
	char type;
	int jobNum;
	int typeNum;
	int processingTime;
	int arrivalTime;
};
struct node {	// node for queues
	job currJob;
	node* next;
};
struct avgNode {	// node for metrics linked list
	int queueSize;
	avgNode* next;
};

class ProcessQueue {
private:
	node* waitlist;
public:
	ProcessQueue() { waitlist = nullptr; };
	~ProcessQueue();
	bool IsEmpty();
	void Enqueue(const job newJob);
	job Dequeue();
	int Size();
	int GetArrivalTime();
	int GetTotalProcessTime();
};

#endif 

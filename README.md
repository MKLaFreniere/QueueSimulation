# QueueSimulation
My final project for my second C++ course. 

To try and explain this project simply, there are a set of queues that Jobs will line up for and be processed. 
Each Job is different in that it has different attributes when being processed. The idea of the project is to
find out how many processors are needed to most efficiently take care of every job, through a simulation. 

The program is able to first generate a set of jobs through the Generator.cpp. A sample result of this is the 
JobData.txt where the attributes of the job are noted. The first column is what type of job it is (A, B, C). The
second column is what time t that the job arrives. The third is how much time t the job needs to be processed when
it is infront of a queue. Each processor has its own queue that the job can enter to be processed.

Log.txt and Metrics.txt are a sample of what is generated after the program finishes the simulation. Log.txt shows
what is happening at each time t during the simulation. Each processor shows its status at the time, as well as the queue
where jobs would wait if all processors are full. Note that the queue is mostly empty in the sample Log.txt because
this specific case with 4 processors is the most efficient. Adding or removing them would create very different results.
Metrics.txt shows the final metrics of the simulation at time = 500 and time = 10000. In this specific case with the given
JobData.txt, this is the most efficient it can be. 

This was a fun project to do, especially as at the time I had recently learned about linked lists and wanted to give
them a try. This was actually a group project meant for 2 people, but as is the case with many college projects my teammate 
didn't contribute to the project at all. This makes me proud that I could complete a piece of programming like this given
that the project was meant for two people. 

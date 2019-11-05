// userkernel.cc 
//	Initialization and cleanup routines for the version of the
//	Nachos kernel that supports running user programs.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "synchconsole.h"
#include "userkernel.h"
#include "synchdisk.h"

//----------------------------------------------------------------------
// UserProgKernel::UserProgKernel
// 	Interpret command line arguments in order to determine flags 
//	for the initialization (see also comments in main.cc)  
//----------------------------------------------------------------------

UserProgKernel::UserProgKernel(int argc, char **argv) 
		: ThreadedKernel(argc, argv)
{
    debugUserProg = FALSE;
	execfileNum=0;
	priorityNum=0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-s") == 0) {
        ASSERT(testingScheduling != TRUE);
	    debugUserProg = TRUE;
	}
	else if (strcmp(argv[i], "-e") == 0) {
        ASSERT(testingScheduling != TRUE);
		execfile[++execfileNum]= argv[++i];
	}
	else if (strcmp(argv[i], "-p") == 0) {
        ASSERT(testingScheduling != TRUE);
		priority[++priorityNum]= argv[++i];
	}
    	 else if (strcmp(argv[i], "-u") == 0) {
		cout << "===========The following argument is defined in userkernel.cc" << endl;
		cout << "Partial usage: nachos [-s]\n";
		cout << "Partial usage: nachos [-u]" << endl;
		cout << "Partial usage: nachos [-e] [filename]" << endl;
		cout << "Partial usage: nachos [-p] [priority]" << endl;
	}
	else if (strcmp(argv[i], "-h") == 0) {
		cout << "argument 's' is for debugging. Machine status  will be printed " << endl;
		cout << "argument 'e' is for execting file." << endl;
		cout << "argument 'p' is for setting priority of execting file." << endl;
		cout << "atgument 'u' will print all argument usage." << endl;
		cout << "For example:" << endl;
		cout << "	./nachos -s : Print machine status during the machine is on." << endl;
		cout << "	./nachos -e file1 -e file2 : executing file1 and file2."  << endl;
	}
    }

    if (priorityNum != 0)
    {
        ASSERT(priorityNum == execfileNum);
    }
}

//----------------------------------------------------------------------
// UserProgKernel::Initialize
// 	Initialize Nachos global data structures.
//----------------------------------------------------------------------

void
UserProgKernel::Initialize()
{
    ThreadedKernel::Initialize();	// init multithreading

    machine = new Machine(debugUserProg);
    fileSystem = new FileSystem();
#ifdef FILESYS
    synchDisk = new SynchDisk("New SynchDisk");
#endif // FILESYS
}

//----------------------------------------------------------------------
// UserProgKernel::~UserProgKernel
// 	Nachos is halting.  De-allocate global data structures.
//	Automatically calls destructor on base class.
//----------------------------------------------------------------------

UserProgKernel::~UserProgKernel()
{
    delete fileSystem;
    delete machine;
#ifdef FILESYS
    delete synchDisk;
#endif
}

//----------------------------------------------------------------------
// UserProgKernel::Run
// 	Run the Nachos kernel.  For now, just run the "halt" program. 
//----------------------------------------------------------------------
void
ForkExecute(Thread *t)
{
	t->space->Execute(t->getName());
}

void
UserProgKernel::Run()
{
	cout << "Total user threads number is " << execfileNum << endl;
	for (int n=1;n<=execfileNum;n++)
	{
		t[n] = new Thread(execfile[n]);
		t[n]->space = new AddrSpace();
        if (priorityNum)
            t[n]->setPriority(atoi(priority[n]));
        else
            t[n]->setPriority(1);
		t[n]->Fork((VoidFunctionPtr) &ForkExecute, (void *)t[n]);
		cout << "Thread " << execfile[n] << " is executing." << endl;
	}

    ThreadedKernel::Run();
}

//----------------------------------------------------------------------
// UserProgKernel::SelfTest
//      Test whether this module is working.
//----------------------------------------------------------------------
#define numTestThread 5

void
SimpleSimulateBurst(int burstTime)
{
    Thread *thread = kernel->currentThread;
    kernel->alarm->WaitUntil(thread->getArrivalTime());
    int oldTime;
    while((oldTime = thread->getBurstTime()) > 0)
    {
        if (kernel->interrupt->getStatus() == SystemMode)
            thread->setBurstTime(oldTime - SystemTick);
        else
            thread->setBurstTime(oldTime - UserTick);
        
        cout << endl << kernel->stats->totalTicks << ": " << thread->getName() << " remain: " << thread->getBurstTime() << endl;
        kernel->scheduler->Print(); 
        kernel->interrupt->OneTick();
    }
    cout << thread->getName() << " done!" << endl;
}

void
UserProgKernel::SelfTest() {
    // ThreadedKernel::SelfTest();
    
    if (testingScheduling)
    {
        Thread *t[numTestThread];
        char *name[] = {"t1", "t2", "t3", "t4", "t5"};
        int arrivalTime[] = {1, 1, 2, 3, 4};
        int burstTime[]   = {1, 2, 3, 2, 1};
        int priority[]    = {2, 2, 3, 4, 1};

        cout << "SelfTest Start" << endl;

        for (int i = 0; i < numTestThread; ++i)
        {
            t[i] = new Thread(name[i]);
            t[i]->space = new AddrSpace();
            t[i]->setArrivalTime((arrivalTime[i] + 10) * TimerTicks);
            t[i]->setBurstTime(burstTime[i] * TimerTicks);
            t[i]->setPriority(priority[i]);
            t[i]->Fork((VoidFunctionPtr) &SimpleSimulateBurst, (void *)burstTime[i]);
        }
    }
}

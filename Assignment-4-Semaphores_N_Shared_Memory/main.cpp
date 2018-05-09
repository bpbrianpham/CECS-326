#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <ctime>
#include <cstdlib>
#include "semaphore.cpp"
using namespace std;

srand(time(NULL));

enum {UVsemaphore}; 

void calculate(SEMAPHORE &, bool *, string);
void parent_cleanup(int arr[], SEMAPHORE &, int schmid);

int main(){
	int shmid = shmget(IPC_PRIVATE, sizeof(bool), PERMS);
	bool *shmBUF = (bool *)shmat(shmid, 0, SHM_RND);
	*shmBUF = true;

	pid_t child;

	SEMAPHORE sem(1); 
	sem.V(UVsemaphore); 
	sem.V(UVsemaphore);

	int arr[4];

	child = fork();
	if (child){
		arr[0] = child;
		child = fork();
		if(child){
			arr[1] = child;
			child = fork();
			if(child){
				arr[2] = child;
				child = fork();
				if(child){
					arr[3] = child;
				}else{//child D
					while(true){calculate(sem, shmBUF, "D");}
				}
			}else{//child C
				while(true){calculate(sem, shmBUF, "C");}
			}
		}else{//child B
			while(true){calculate(sem, shmBUF, "B");}
		}
	}else{//child A
		while(true){calculate(sem, shmBUF, "A");}
	}


    parent_cleanup(arr, sem, shmid);

    return 0;
}

void calculate(SEMAPHORE &sem, bool *shmBUF, string childLetter) {
	int randNum;

	bool v = *shmBUF;

	if(v){
		int V = 962094883;
		*shmBUF = false;

		do{
			randNum = rand() % 100000;
			cout << childLetter << " : " << randNum << endl;
		}while(randNum % V == 0 || randNum < 100);

		*shmBUF = true;
	}else{
		int U = 827395609;

		do{
			randNum = rand() % 100000;
			cout << childLetter << " : " << randNum << endl;
		}while(randNum % U == 0 || randNum < 100);
	}

	sem.P(UVsemaphore);
} 

void parent_cleanup (int arr[], SEMAPHORE &sem, int shmid) {
	string choice = "";
	do{		
		cout << "Type '!wq' to quit. " << endl;
		cin >> choice;
	}while(choice.compare("!wq") != 0);

	cout << "Killing all children." << endl;
	for (int id = 0; id<4; id++){
		kill(arr[id],SIGTERM);
	}
	shmctl(shmid, IPC_RMID, NULL);
	cout << "Ending the parent.\nExiting..." << endl;
	sem.remove();
	exit(0);
} // parent_cleanup

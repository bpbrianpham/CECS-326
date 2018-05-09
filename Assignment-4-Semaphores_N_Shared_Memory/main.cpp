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
#include "semaphore.cpp"
using namespace std;

enum {UVsemaphore}; 

void calculate(SEMAPHORE &, bool *);
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
				}else{
					while(true){calculate(sem, shmBUF);}
				}
			}else{
				while(true){calculate(sem, shmBUF);}
			}
		}else{
			while(true){calculate(sem, shmBUF);}
		}
	}else{
		while(true){calculate(sem, shmBUF);}
	}


    parent_cleanup(arr, sem, shmid);

    return 0;
}

void calculate(SEMAPHORE &sem, bool *shmBUF) {
	int randNum;

	bool v = *shmBUF;

	if(v){
		int V = 962094883;
		*shmBUF = false;

		do{
			randNum = rand() % 100;
		}while(randNum % V == 0);

		*shmBUF = true;
	}else{
		int U = 827395609;

		do{
			randNum = rand() % 100;
		}while(randNum % U == 0);
	}

	sem.P(UVsemaphore);
} 

void parent_cleanup (int arr[], SEMAPHORE &sem, int shmid) {
	string choice = "";
	do{		
		cout << "Type '!wq' to quit. " << endl;
		cin >> choice;
	}while(choice.compare("!wq") == 0);

	cout << "Killing all children." << endl;
	for (int id = 0; id<4; id++){
		kill(arr[id],SIGTERM);
	}
	shmctl(shmid, IPC_RMID, NULL);
	cout << "Ending the parent.\nExiting..." << endl;
	sem.remove();
	exit(0);
} // parent_cleanup

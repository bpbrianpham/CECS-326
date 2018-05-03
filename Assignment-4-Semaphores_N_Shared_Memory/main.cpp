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
#include "semaphore.h"

using namespace std;

//the target to be factored
const int U = 827395609
const int V = 962094883

const int MAXCHAR = 10;
const int BUFFSIZE = 3;
enum {PUT_ITEM, TAKE_ITEM}; // set up names of my 2 semaphores

void producer_proc(SEMAPHORE &, char *);
void parent_cleanup(SEMAPHORE &, int);
void consumer_proc(SEMAPHORE &, char *);

int main(){
	int shmid;
	char *shmBUF;

	SEMAPHORE sem(2); // Constructing an Object with 2 semaphores (sem are set to zero when initialize)
	sem.V(PUT_ITEM); // Incrementing each PUT_ITEM by 1
	sem.V(PUT_ITEM);
	sem.V(PUT_ITEM); // PUT_ITEM = 3 

    child1 = fork();
	if (child1){ //parent
		//Todo
	}
	else{ 
		child2 = fork();
		if(child2){ //child 1
			//Todo
		}
		else{
			child3 = fork();
			if(child3){ //child 2
				//Todo
			}
			else{
				child4 = fork();
				if(child4){ //child 3
					//Todo
				}
				else{
					//child 4 - Todo
				}
			}
		}
	}

    exit(0);
}

void consumer_proc(SEMAPHORE &sem, char *shmBUF) {
	char tmp;

	for(int k=0; k<MAXCHAR; k++){
		sem.P(TAKE_ITEM);
		tmp = *(shmBUF+k%BUFFSIZE); // shmBUF = shared memeory & k%BUFFSIZE = accese which memory (K = 0 --> 9) 
		sem.V(PUT_ITEM);			// However it is % of BUFFSIZE so K = 0,1,2,0,1,2,0,1,2.....
		cout << "(" << getpid() << ")  " 
				<< "buf[" << k%BUFFSIZE << "] "
				<< tmp << endl; // <--- this endl is important becasue it will flush buffer
	}
} // child_proc

void producer_proc(SEMAPHORE &sem, char *shmBUF) {

	char data[128];
	cout << "(" << getpid() << ")  Please enter a string --> ";
	cin.getline(data, 127);

	char input;
	for(int k=0; k<MAXCHAR; k++){
		input = data[k];
		sem.P(PUT_ITEM);
		*(shmBUF+(k%BUFFSIZE)) = input;
		sem.V(TAKE_ITEM);
	}
} // parent_proc

void parent_cleanup (SEMAPHORE &sem, int shmid) {

	int status;			/* child status */
	wait(0);	/* wait for child to exit */
	shmctl(shmid, IPC_RMID, NULL);	/* cleaning up */
	sem.remove();
} // parent_cleanup
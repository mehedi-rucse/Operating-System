/*	Target: To remove shared data inconsistency using Binary Semaphore. 
	Problem: 
	1. to create two child processes for a process to share a data
	2. one child process will increase the shared data
	3. another process will decrease the shared data
	4. main process will only read the shared data
	5. to implement unnamed semaphore to deal with data inconsistency problem.

	How to run: 	$ gcc Assignment5_Unnamed_1810976114_1812176135.c  -o Assignment5_Unnamed_1810976114_1812176135 -pthread
			$ ./Assignment5_Unnamed_1810976114_1812176135	
*/ 
#define _GNU_SOURCE
#include <sys/ipc.h>
#include <stdio.h>
#include <sys/shm.h>
#include <string.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/wait.h>
 


int create_shared_memory(){
	key_t key;
	int shmID;
	key = ftok("/home/mehedi/Desktop/OS_CLASS/Shared Memory/SharedMemory_Reader.c", 'a');//1st parameter should a existing file path name
	shmID = shmget(key, 1024, IPC_CREAT | 0666);

	return shmID;
}
int create_shm_for_semaphore(){
	key_t key;
	int shmID;
	key = ftok("/home/mehedi/Desktop/OS_CLASS/Shared Memory/SharedMemory_Writer.c", 'o');//1st parameter should a existing file path name
	shmID = shmget(key, 1024, IPC_CREAT | 0666);

	return shmID;
}

void write_to_shm(int x){ 
	int shmID = create_shared_memory();	
				
	// Attach shared memory with the ddress space of the process.
	char *str = shmat(shmID, NULL, 0);
	
	// Convert integer into a string.
	char num[100];
	sprintf(num, "%d", x);
	
	// Put integer data into the shared memory.	
	strcpy(str, num);
	
	// Detach the shared memory segment.
	shmdt(str);
}

int read_from_shm(){ 
	int shmID = create_shared_memory();
	
	// Attach shared memory with the address space of the process.
	char *str = shmat(shmID, NULL, 0);
	
	// Convert string to integer
	int num = (int) strtol(str, (char **)NULL, 10);
	
	// Detach the shared memory segment.
	shmdt(str);
	
	return num;
}
void child_error_check(pid_t childPID){
    if(childPID < 0){
        printf("Error  while creating child process!!!");
        exit(-1);
    }
}


int main(){
	sem_t * sem;
	pid_t childPID1,childPID2;
	int a, b, x, shmID;

	// Put shareable data into shared memory so that both parent and child can perform operation on it.
	x = 10; // Shared data
	write_to_shm(x);

	
	// Initialize binary semaphore.
    shmID = create_shm_for_semaphore();//creating shared memory for semaphore
    sem = shmat(shmID, NULL, 0);// attaching semaphore to that shared memory
	
	sem_init(sem, 1, 1); // 2nd parameter--> 0: thread, 1: process
	
	// Create child processes.
	childPID1 = fork();
	child_error_check(childPID1);
	
	// This Child process will increase value of shared data 
	if (childPID1 == 0){ // 1st Child Process
		
		sem_wait(sem);
		
		a = read_from_shm();		
		printf("x: %d in Child [PID: %d] of Parent[PID: %d] in [Core: %d] Before Addition\n", a,getpid(),getppid(),sched_getcpu());
		a = a + 1;
		write_to_shm(a);
		b = read_from_shm();
		printf("x: %d in Child [PID: %d] of Parent[PID: %d] in [Core: %d] After Addition\n", b,getpid(),getppid(), sched_getcpu());
		
		sem_post(sem);
	}

	else{
		// Create child processes.
		childPID2 = fork();
		child_error_check(childPID2);

		//This Child process will decrease value of shared data. 
		if(childPID2 == 0){ // 2nd Child process
			
			sem_wait(sem);
			
			a = read_from_shm();		
			printf("x: %d in Child [PID: %d] of Parent[PID: %d] in [Core: %d] Before Subtraction\n", a,getpid(),getppid(),sched_getcpu());
			a = a - 1;
			write_to_shm(a);
			b = read_from_shm();
			printf("x: %d in Child [PID: %d] of Parent[PID: %d] in [Core: %d] After Subtraction\n", b,getpid(),getppid(), sched_getcpu());
			
			sem_post(sem);

		}
		else {
			
			// Wait until the child process finishes its task.
			waitpid(childPID1,NULL,0);
			waitpid(childPID2,NULL,0);
		}
	}
	
	shmdt(sem);//detaching shared memory of semaphore
	return 0;
}
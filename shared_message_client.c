//Christopher Shorter
//cws68
//HW 6
#include <stdio.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <semaphore.h> 
#include <stdbool.h>

void* setupSHM(char *name){
	const int SIZE = 4096;
	int shm_fd;
    void *ptr;
    
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE);
	
	ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        printf("Map failed\n");
        exit(-1);
    }
	
	return ptr;
}

void* getContentsSHM(char *name){
	const int SIZE = 4096;
	int shm_fd = shm_open(name, O_RDWR, 0666);
    if(shm_fd ==-1){
        printf("shared memory failed \n");
        exit(-1);
    }
	
	void* ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        printf("Map failed\n");
        exit(-1);
    }
	return ptr;
}

void closeSHM(char* name){
	if(shm_unlink(name) == -1){
        printf("Error removing %s\n", name);
        exit(-1);
    }
}

int main(){
	void* content_ptr = getContentsSHM("message");
	sem_t* sem_ptr = getContentsSHM("semaphore");
	
	bool done = false;
	while(!done){
		sem_ptr = getContentsSHM("semaphore");
		sem_wait(sem_ptr);
		content_ptr = getContentsSHM("message");
		printf("Message: %s", (char*)content_ptr);
		sem_post(sem_ptr);
		
		int choice = 0;
		char buffer[1024];
		printf("0. Quit\n1. Change Message\n2. Check Message\n");
		fflush(stdout);
		scanf("%d", &choice);
		fgets(buffer, sizeof(buffer), stdin);
		switch(choice){
			case 0:
				done = true;
				sem_wait(sem_ptr);
				sprintf(content_ptr, "%s", "client has quit\n");
				sem_post(sem_ptr);
				break;
			case 1:
				sem_wait(sem_ptr);
				printf("Enter new message:\n");
				fflush(stdout);
				fgets(buffer, sizeof(buffer), stdin);
				sprintf(content_ptr, "%s", buffer);
				sem_post(sem_ptr);
				break;
			case 2:
				break;
			default:
				printf("Invalid Command\n");
				fflush(stdout);
				break;
		}
	}

}
	
	
	
	
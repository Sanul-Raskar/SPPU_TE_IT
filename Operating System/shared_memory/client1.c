/*
Sanul Raskar
TE IT A2
331059
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define SHM_SIZE 50

int main()
{
	key_t key = 5056;
	int shmID, length;
	char *shm, *c,*temp;

	shmID = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
	if (shmID < 0)
	{
		perror("shmget error");
		return 0;
	}

	if ((shm = shmat(shmID, NULL, 0)) == (char *)-1)
	{
		perror("shmat error");
		return 0;
	}

	temp = shm;
	c = shm;
	*c = 'Y';
	*c++;
	*c++;
	printf("Client 1 : Data read from Shared Memory with key 5056\n");
	while(*c!='\0'){
		putchar(*c);
		*c++;
	}
	printf("\n");
	return 0;
}

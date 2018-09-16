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
#include <string.h>
#include <unistd.h>
#include <time.h>
#define SHM_SIZE 50

int main()
{
    key_t key = 5056;
    int shmID, count = 2, length = 100, flag1 = 0, flag2 = 0, deallocateFlag, f;
    char *shm, *temp, *client1, *client2, c, *shmTemp;
    char *name = (char *)malloc(length * sizeof(char));
    time_t rawtime1, rawtime2;
    struct tm *timeinfo1, *timeinfo2;

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
    name[0] = 'N';
    name[1] = 'N';
    printf("Enter data to write on shared memory\n");
    while ((c = getchar()) != '\n')
    {
        if (count >= length)
            name = realloc(name, (length += 10) * sizeof(char));
        name[count++] = c;
    }
    name[count] = '\0';
    temp = shm;
    for (int i = 0; i < count; i++)
    {
        *temp = name[i];
        *temp++;
    }
    temp = NULL;
    shmTemp = shm;
    client1 = shmTemp;
    *shmTemp++;
    client2 = shmTemp;
    printf("Server : Data written on Shared Memory with key 5056\n");
    while (1)
    {

        if (*client1 == 'Y' && flag1 == 0)
        {
            time(&rawtime1);
            timeinfo1 = localtime(&rawtime1);
            printf("Server: Client 1 read at  local time and date: %s", asctime(timeinfo1));
            flag1 = 1;
        }
        if (*client2 == 'Y' && flag2 == 0)
        {
            time(&rawtime2);
            timeinfo2 = localtime(&rawtime2);
            printf("Server: Client 2 read at local time and date: %s", asctime(timeinfo2));
            flag2 = 1;
        }
        if (flag1 == 1 && flag2 == 1)
        {
            free(name);
            deallocateFlag = shmdt(shm);
            if (deallocateFlag == -1)
                printf("Error de-linking shared memory\n");
            else
            {
                f = shmctl(shmID, IPC_RMID, NULL);
                if (f == -1)
                    printf("Error in deallocating shared memory");
            }

            exit(0);
        }
    }
    return 0;
}

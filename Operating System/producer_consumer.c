/*
 * Sanul Raskar
 * TE IT A2
 * 331059
 * */
/*
 * Producer Consumer
 */

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>


#define BUFFER_SIZE 20
#define RAND_DIVISOR 10000000

int buffer[BUFFER_SIZE];
int counter = -1;
pthread_mutex_t mutex;
sem_t full, empty;

bool addInBuffer(int);

bool removeFromBuffer(int *);

void init();

bool addInBuffer(int element) {
    if (counter < BUFFER_SIZE) {
        buffer[++counter] = element;
        return true;
    } else
        return false;
}

bool removeFromBuffer(int *item) {

    if (counter >= 0) {
        *item = buffer[counter--];
        return true;
    } else
        return false;
}

void *producer(void *arg) {
    int bufferElement;
    while (1) {
        sleep(1);
        bufferElement = rand() / RAND_DIVISOR;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        if (addInBuffer(bufferElement))
            printf("Produced item is %d\n ", bufferElement);
        else
            printf("Producer Error Occured\n");

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *parameter) {
    int bufferElement;
    while (1) {
        sleep(1);
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        if (removeFromBuffer(&bufferElement))
            printf("Consumer item is %d\n", bufferElement);
        else
            printf("Consumer error occured\n");
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

void init() {
    pthread_mutex_init(&mutex, NULL);
    sem_init(&full, 0, 0);
    sem_init(&empty, 1, 20);
}

int main() {
    pthread_t tid[30];
    int producerNumber, consumerNumber;
    init();
    printf("Enter number of producers -> ");
    scanf("%d", &producerNumber);
    printf("\nEnter number of consumers -> ");
    scanf("%d", &consumerNumber);

    for (int k = 0; k < producerNumber; k++)
        pthread_create(&tid[k], NULL, producer, NULL);


    for (int k = 0; k < consumerNumber; k++)
        pthread_create(&tid[k], NULL, consumer, NULL);

    sleep(20);

    return 0;
}

/*
 OUTPUT

 sanul@sanul-HP-Notebook:~/CLionProjects/producer_consumer$ gcc main.c -lpthread
sanul@sanul-HP-Notebook:~/CLionProjects/producer_consumer$ ./a.out
Enter number of producers ->
2

Enter number of consumers -> 2
Produced item is 180
 Consumer item is 180
Produced item is 84
 Consumer item is 84
Produced item is 168
 Produced item is 171
 Consumer item is 171
Consumer item is 168
Produced item is 195
 Produced item is 42
 Consumer item is 42
Consumer item is 195
Produced item is 71
 Produced item is 164
 Consumer item is 164
Consumer item is 71
Produced item is 59
 Produced item is 118
 Consumer item is 118
Consumer item is 59
Produced item is 102
 Consumer item is 102
Produced item is 135
 Consumer item is 135
Produced item is 78
 Consumer item is 78
Produced item is 110
 Consumer item is 110
Produced item is 204
 Produced item is 196
 Consumer item is 196
Consumer item is 204
Produced item is 136
 Produced item is 154
 Consumer item is 154
Consumer item is 136
Produced item is 30
 Consumer item is 30
Produced item is 130
 Consumer item is 130
Produced item is 3
 Produced item is 52
 Consumer item is 52
Consumer item is 3
Produced item is 29
 Produced item is 172
 Consumer item is 172
Consumer item is 29
Produced item is 33
 Produced item is 86
 Consumer item is 86
Consumer item is 33
Produced item is 27
 Consumer item is 27
Produced item is 23
 Consumer item is 23
Produced item is 214
 Consumer item is 214
Produced item is 46
 Consumer item is 46
Produced item is 110
 Consumer item is 110
Produced item is 180
 Consumer item is 180
Produced item is 131
 Consumer item is 131
Produced item is 63
 Consumer item is 63
Produced item is 136
 Consumer item is 136
Produced item is 112
 Consumer item is 112
Produced item is 105
 Consumer item is 105
Produced item is 208
 Consumer item is 208
sanul@sanul-HP-Notebook:~/CLionProjects/producer_consumer$ ./a.out
Enter number of producers -> 0

Enter number of consumers -> 2
sanul@sanul-HP-Notebook:~/CLionProjects/producer_consumer$ ./a.out
Enter number of producers -> 2

Enter number of consumers -> 0
Produced item is 180
 Produced item is 84
 Produced item is 168
 Produced item is 171
 Produced item is 195
 Produced item is 42
 Produced item is 71
 Produced item is 164
 Produced item is 59
 Produced item is 118
 Produced item is 102
 Produced item is 135
 Produced item is 78
 Produced item is 110
 Produced item is 204
 Produced item is 196
 Produced item is 136
 Produced item is 154
 Produced item is 30
 Produced item is 130
 sanul@sanul-HP-Notebook:~/CLionProjects/producer_consumer$ ./a.out
Enter number of producers -> 0

Enter number of consumers -> 0
sanul@sanul-HP-Notebook:~/CLionProjects/producer_consumer$

 */

/*
 * Sanul Raskar
 * TE IT A2
 * 331059
 * */

/*
 * Dining Philosopher problem
 * */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<semaphore.h>
#include <unistd.h>

#define MAX 5
#define FOOD 30
#define DELAY 5000
pthread_mutex_t mutex, food_lock;
sem_t S[MAX];
int phil_num[MAX] = {0, 1, 2, 3, 4}, state[MAX];

int leftOf(int);

int rightOf(int);

void test(int);

void take_fork(int);

void put_fork(int);

int foodOnTable();

void *philosopher(void *);

int leftOf(int num) {
    return ((num + 4) % MAX);
}

int rightOf(int num) {
    return ((num + 1) % MAX);
}

int foodOnTable() {
    static int food = FOOD;
    int myFood;
    pthread_mutex_lock(&food_lock);
    if (food > 0)
        food--;
    myFood = food;
    pthread_mutex_unlock(&food_lock);
    return myFood;
}

void test(int philosopher_num) {
    if (state[philosopher_num] == 1 && state[leftOf(philosopher_num)] != 2 && state[rightOf(philosopher_num)] != 2) {
        state[philosopher_num] = 2;
        sleep(1);
        printf("Philosopher %d takes leftFork %d & rightFork %d  & starts eating\n", philosopher_num + 1,
               leftOf(philosopher_num) + 1,
               philosopher_num + 1);
        sem_post(&S[philosopher_num]);
    }
}

void take_fork(int philosopher_num) {
    pthread_mutex_lock(&mutex);
    state[philosopher_num] = 1;
    printf("Philosopher %d is Hungry\n", philosopher_num + 1);
    sleep(1);
    test(philosopher_num);
    pthread_mutex_unlock(&mutex);
    sem_wait(&S[philosopher_num]);
    sleep(1);
}

void put_fork(int philosopher_num) {
    pthread_mutex_lock(&mutex);
    state[philosopher_num] = 0;
    printf("Philosopher %d puts leftFork %d & rightFork %d \n", philosopher_num + 1, leftOf(philosopher_num) + 1,
           philosopher_num + 1);
    printf("Philosopher %d is thinking \n", philosopher_num + 1);
    test(leftOf(philosopher_num));
    test(rightOf(philosopher_num));
    pthread_mutex_unlock(&mutex);
}

void *philosopher(void *arg) {
  int f;
    while (f = foodOnTable()) {
        int *i = arg;
        if (*i == 0)
           sleep(30);
        sleep(1);
        take_fork(*i);
        put_fork(*i);
    }
     return NULL;
}

int main() {
    pthread_t tid[MAX];
    int i;
    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < MAX; i++) {
        pthread_create(&tid[i], NULL, philosopher, &phil_num[i]);
        printf("Philosopher %d is thinking \n", i + 1);
    }
    for (i = 0; i < MAX; i++)
        pthread_join(tid[i], NULL);

    exit(0);
}

/*
sanul@sanul-HP-Notebook:~/github/SPPU_TE_IT/Operating System$ gcc dining_Philosopher.c -lpthread
sanul@sanul-HP-Notebook:~/github/SPPU_TE_IT/Operating System$ ./a.out
Philosopher 1 is thinking
Philosopher 2 is thinking
Philosopher 3 is thinking
Philosopher 4 is thinking
Philosopher 5 is thinking
Philosopher 4 is Hungry
Philosopher 4 takes leftFork 3 & rightFork 4  & starts eating
Philosopher 2 is Hungry
Philosopher 2 takes leftFork 1 & rightFork 2  & starts eating
Philosopher 3 is Hungry
Philosopher 2 puts leftFork 1 & rightFork 2
Philosopher 2 is thinking
Philosopher 5 is Hungry
Philosopher 2 is Hungry
Philosopher 2 takes leftFork 1 & rightFork 2  & starts eating
Philosopher 4 puts leftFork 3 & rightFork 4
Philosopher 4 is thinking
Philosopher 5 takes leftFork 4 & rightFork 5  & starts eating
Philosopher 2 puts leftFork 1 & rightFork 2
Philosopher 2 is thinking
Philosopher 3 takes leftFork 2 & rightFork 3  & starts eating
Philosopher 5 puts leftFork 4 & rightFork 5
Philosopher 5 is thinking
Philosopher 4 is Hungry
Philosopher 5 is Hungry
Philosopher 5 takes leftFork 4 & rightFork 5  & starts eating
Philosopher 2 is Hungry
Philosopher 5 puts leftFork 4 & rightFork 5
Philosopher 5 is thinking
Philosopher 3 puts leftFork 2 & rightFork 3
Philosopher 3 is thinking
Philosopher 2 takes leftFork 1 & rightFork 2  & starts eating
Philosopher 4 takes leftFork 3 & rightFork 4  & starts eating
Philosopher 5 is Hungry
Philosopher 3 is Hungry
Philosopher 4 puts leftFork 3 & rightFork 4
Philosopher 4 is thinking
Philosopher 5 takes leftFork 4 & rightFork 5  & starts eating
Philosopher 2 puts leftFork 1 & rightFork 2
Philosopher 2 is thinking
Philosopher 3 takes leftFork 2 & rightFork 3  & starts eating
Philosopher 5 puts leftFork 4 & rightFork 5
Philosopher 5 is thinking
Philosopher 4 is Hungry
Philosopher 3 puts leftFork 2 & rightFork 3
Philosopher 3 is thinking
Philosopher 4 takes leftFork 3 & rightFork 4  & starts eating
Philosopher 2 is Hungry
Philosopher 2 takes leftFork 1 & rightFork 2  & starts eating
Philosopher 5 is Hungry
Philosopher 2 puts leftFork 1 & rightFork 2
Philosopher 2 is thinking
Philosopher 3 is Hungry
Philosopher 4 puts leftFork 3 & rightFork 4
Philosopher 4 is thinking
Philosopher 3 takes leftFork 2 & rightFork 3  & starts eating
Philosopher 5 takes leftFork 4 & rightFork 5  & starts eating
Philosopher 2 is Hungry
Philosopher 5 puts leftFork 4 & rightFork 5
Philosopher 5 is thinking
Philosopher 4 is Hungry
Philosopher 5 is Hungry
Philosopher 5 takes leftFork 4 & rightFork 5  & starts eating
Philosopher 1 is Hungry
Philosopher 5 puts leftFork 4 & rightFork 5
Philosopher 5 is thinking
Philosopher 1 takes leftFork 5 & rightFork 1  & starts eating
Philosopher 3 puts leftFork 2 & rightFork 3
Philosopher 3 is thinking
Philosopher 4 takes leftFork 3 & rightFork 4  & starts eating
Philosopher 5 is Hungry
Philosopher 4 puts leftFork 3 & rightFork 4
Philosopher 4 is thinking
Philosopher 3 is Hungry
Philosopher 3 takes leftFork 2 & rightFork 3  & starts eating
Philosopher 1 puts leftFork 5 & rightFork 1
Philosopher 1 is thinking
Philosopher 5 takes leftFork 4 & rightFork 5  & starts eating
Philosopher 4 is Hungry
Philosopher 5 puts leftFork 4 & rightFork 5
Philosopher 5 is thinking
Philosopher 3 puts leftFork 2 & rightFork 3
Philosopher 3 is thinking
Philosopher 2 takes leftFork 1 & rightFork 2  & starts eating
Philosopher 4 takes leftFork 3 & rightFork 4  & starts eating
Philosopher 5 is Hungry
Philosopher 4 puts leftFork 3 & rightFork 4
Philosopher 4 is thinking
Philosopher 5 takes leftFork 4 & rightFork 5  & starts eating
Philosopher 3 is Hungry
Philosopher 5 puts leftFork 4 & rightFork 5
Philosopher 5 is thinking
Philosopher 4 is Hungry
Philosopher 4 takes leftFork 3 & rightFork 4  & starts eating
Philosopher 2 puts leftFork 1 & rightFork 2
Philosopher 2 is thinking
Philosopher 5 is Hungry
Philosopher 2 is Hungry
Philosopher 2 takes leftFork 1 & rightFork 2  & starts eating
Philosopher 4 puts leftFork 3 & rightFork 4
Philosopher 4 is thinking
Philosopher 5 takes leftFork 4 & rightFork 5  & starts eating
Philosopher 2 puts leftFork 1 & rightFork 2
Philosopher 2 is thinking
Philosopher 3 takes leftFork 2 & rightFork 3  & starts eating
Philosopher 4 is Hungry
Philosopher 5 puts leftFork 4 & rightFork 5
Philosopher 5 is thinking
Philosopher 2 is Hungry
Philosopher 3 puts leftFork 2 & rightFork 3
Philosopher 3 is thinking
Philosopher 2 takes leftFork 1 & rightFork 2  & starts eating
Philosopher 4 takes leftFork 3 & rightFork 4  & starts eating
Philosopher 2 puts leftFork 1 & rightFork 2
Philosopher 2 is thinking
Philosopher 4 puts leftFork 3 & rightFork 4
Philosopher 4 is thinking
Philosopher 1 is Hungry
Philosopher 1 takes leftFork 5 & rightFork 1  & starts eating
Philosopher 1 puts leftFork 5 & rightFork 1
Philosopher 1 is thinking
sanul@sanul-HP-Notebook:~/github/SPPU_TE_IT/Operating System$


*/

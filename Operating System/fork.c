#include <stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

void accept();

void display1();

void display2();

void swap(int *xp, int *yp);

void bubblesort();

void bubblesort1();

int number[20], num[20], n;

void accept() {
    printf("How many numbers you want to sort?\n");
    scanf("%d", &n);
    printf("Enter the numbers to be sorted\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &number[i]);
        num[i] = number[i];
    }
}

void display1() {
    for (int i = 0; i < n; i++) {
        printf("%d, ", number[i]);
    }
    printf("\n");


}

void display2() {
    for (int i = 0; i < n; i++) {
        printf("%d, ", num[i]);
    }
    printf("\n");

}


void bubblesort() {
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (number[j] > number[j + 1])
                swap(&number[j], &number[j + 1]);


}

void bubblesort1() {
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (num[j] < num[j + 1])
                swap(&num[j], &num[j + 1]);

}


void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

int main() {
    pid_t cpid;
    accept();

    cpid = fork();

    if (cpid == -1)
        printf("Error\n");

    if (cpid == 0) {
        printf("Child process has been created with PID %d \n",getpid());
        bubblesort();
        display1();
        printf("Child Exits\n");
    } else {
        printf("This is Parent process pid=%d\n",getpid());

        bubblesort1();
        display2();
        printf("Parent waits\n");
        wait(NULL);
        printf("Parent exits\n");

    }
    return 0;
}

/*
sanul@sanul-HP-Notebook:~/Desktop$ gcc fork.c
sanul@sanul-HP-Notebook:~/Desktop$ ./a.out
How many numbers you want to sort?
5
Enter the numbers to be sorted
3
4
1
2
5
This is Parent process pid=11783
5, 4, 3, 2, 1, 
Parent waits
Child process has been created with PID 11787 
1, 2, 3, 4, 5, 
Child Exits
Parent exits
sanul@sanul-HP-Notebook:~/Desktop$ 


*/

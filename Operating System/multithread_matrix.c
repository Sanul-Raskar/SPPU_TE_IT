/*
 * Sanul Raskar
 * TE IT A2
 * 331059
 *
 * Matrix Multiplication using pthread library
 *
 * */


#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

void printMatrix(int mat[3][3]);

int A[3][3], B[3][3], C[3][3],
        A[3][3] = {{1, 1, 1},
                   {1, 1, 1},
                   {1, 1, 1}},
        B[3][3] = {{1, 1, 1},
                   {1, 1, 1},
                   {1, 1, 1}},
        C[3][3] = {{0, 0, 0},
                   {0, 0, 0},
                   {0, 0, 0}}, thread_counter = 0;


typedef struct index {
    int i, j;
} index;

void printMatrix(int mat[3][3]) {

    int a, b;
    printf("\n");
    for (a = 0; a < 3; a++) {
        printf("\n");
        for (b = 0; b < 3; b++) {
            printf("%d  ", mat[a][b]);
        }
    }
    printf("\n");
}

void *multiplication(void *ind) {
    int count, result = 0;
    index *indices = (index *) ind;
    printf("\nMatrix Multiplication for indices i=%d j=%d \n", indices->i, indices->j);

    for (count = 0; count < 3; count++) {
        printf("A[%d][%d] * B[%d][%d]\n", indices->i, count, count, indices->j);
        result += A[indices->i][count] * B[count][indices->j];
    }
    printf("\n\n");
    pthread_exit((void *) result);
}

int main() {
    pthread_t threadID[10];
    int x, y;
    index *ij_values;
    int final;
    void *result;

    for (x = 0; x < 3; x++)
        for (y = 0; y < 3; y++) {
            ij_values = (index *) malloc(sizeof(index));
            ij_values->i = x;
            ij_values->j = y;

            printf("\nThread created for ID %d\n", thread_counter);
            pthread_create(&threadID[thread_counter++], NULL, multiplication, (void *) ij_values);
        }

    thread_counter = 0;
    for (x = 0; x < 3; x++)
        for (y = 0; y < 3; y++) {
            pthread_join(threadID[thread_counter++], &result);
            final = (int *) result;
            C[x][y] = final;
        }

    printf("\nMatrix A :");
    printMatrix(A);
    printf("\nMatrix B :");
    printMatrix(B);
    printf("\nResultant Matrix C :");
    printMatrix(C);
    return 0;
}

/*Output*/

/*
 sanul@sanul-HP-Notebook:~/CLionProjects/multithread_matrix$ ./a.out

Thread created for ID 0

Thread created for ID 1

Matrix Multiplication for indices i=0 j=0
A[0][0] * B[0][0]

Thread created for ID 2
A[0][1] * B[1][0]
A[0][2] * B[2][0]



Thread created for ID 3

Matrix Multiplication for indices i=0 j=1
A[0][0] * B[0][1]
A[0][1] * B[1][1]
A[0][2] * B[2][1]



Matrix Multiplication for indices i=0 j=2
A[0][0] * B[0][2]
A[0][1] * B[1][2]
A[0][2] * B[2][2]

Thread created for ID 4



Thread created for ID 5

Matrix Multiplication for indices i=1 j=0
A[1][0] * B[0][0]

Thread created for ID 6
A[1][1] * B[1][0]
A[1][2] * B[2][0]



Matrix Multiplication for indices i=1 j=2

Matrix Multiplication for indices i=2 j=0

Thread created for ID 7
A[1][0] * B[0][2]
A[1][1] * B[1][2]
A[1][2] * B[2][2]


A[2][0] * B[0][0]

Thread created for ID 8

Matrix Multiplication for indices i=1 j=1
A[1][0] * B[0][1]
A[1][1] * B[1][1]

Matrix Multiplication for indices i=2 j=1
A[2][0] * B[0][1]
A[2][1] * B[1][1]
A[2][2] * B[2][1]



Matrix Multiplication for indices i=2 j=2
A[2][0] * B[0][2]
A[2][1] * B[1][2]
A[2][2] * B[2][2]


A[2][1] * B[1][0]
A[2][2] * B[2][0]


A[1][2] * B[2][1]



Matrix A :

1  1  1
1  1  1
1  1  1

Matrix B :

1  1  1
1  1  1
1  1  1

Resultant Matrix C :

3  3  3
3  3  3
3  3  3
sanul@sanul-HP-Notebook:~/CLionProjects/multithread_matrix$

 * */


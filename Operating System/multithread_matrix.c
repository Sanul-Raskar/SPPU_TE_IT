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

int **mat1, **mat2, **mat3, r1, c1, r2, c2, thread_counter = 0;
typedef struct index {
    int i, j;
} index;

/*Function Prototypes*/
int **memoryAllocation(int r, int c, int flag);
void printMatrix(int **mat, int r, int c);
void *multiplication(void *ind);
pthread_t *threadArrayAlloaction(int r,int c);
void deallocateMemory(int **A,int Ar,int **B,int Br,int **C,int Cr,pthread_t *D);


int **memoryAllocation(int r, int c, int flag) {
    int **M;
    M = (int **) malloc(r * sizeof(int *));
    for (int i = 0; i < r; i++)
        *(M + i) = (int *) malloc(c * sizeof(int *));

    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) {
            if (flag == 0)
                scanf("%d", (*(M + i) + j));
            else
                *(*(M + i) + j) = 0;
        }

    return M;
}

pthread_t *threadArrayAlloaction(int r,int c){
    int size;
    size = r*c;
    pthread_t *ptr = (pthread_t*)calloc(size, sizeof(pthread_t));
    return ptr;
}

void deallocateMemory(int **A,int Ar,int **B,int Br,int **C,int Cr,pthread_t *D){
    for(int i = 0; i < Ar; i++)
        free(A[i]);
    free(A);

    for(int i = 0; i < Br; i++)
        free(B[i]);
    free(B);

    for(int i = 0; i < Cr; i++)
        free(C[i]);
    free(C);

    free(D);
}
void printMatrix(int **mat, int r, int c) {

    printf("\n");
    for (int i = 0; i < r; i++) {
        printf("\n");
        for (int j = 0; j < c; j++) {
            printf("%d  ", *(*(mat + i) + j));
        }
    }
    printf("\n");
}

void *multiplication(void *ind) {
    int count, result = 0;
    index *indices = (index *) ind;
    printf("Thread in execution with Thread ID : %ld \n",pthread_self());
    for (count = 0; count < r2; count++)
        result += (*(*(mat1 + indices->i) + count)) * (*(*(mat2 + count) + indices->j));
    pthread_exit((void *) result);
}

int main() {
    pthread_t *threadID;
    int x, y, final;
    index *ij_values;
    void *result;

    printf("Enter the number of row and col for matrix 1\n");
    scanf("%d %d", &r1, &c1);
    printf("Enter the number of row and col for matrix 2\n");
    scanf("%d %d", &r2, &c2);

    if (c1 == r2) {
        printf("Enter elements for matrix 1\n");
        mat1 = memoryAllocation(r1, c1, 0);
        printf("Enter elements for matrix 2\n");
        mat2 = memoryAllocation(r2, c2, 0);
        mat3 = memoryAllocation(r1, c2, 1);
        threadID = threadArrayAlloaction(r1,c2);

        for (x = 0; x < r1; x++)
            for (y = 0; y < c2; y++) {
                ij_values = (index *) malloc(sizeof(index));
                ij_values->i = x;
                ij_values->j = y;

                printf("\nThread created count -> %d\n", thread_counter);
                pthread_create((threadID+thread_counter), NULL, multiplication, (void *) ij_values);
                thread_counter++;
            }

        thread_counter = 0;
        for (x = 0; x < r1; x++)
            for (y = 0; y < c2; y++) {
                pthread_join(threadID[thread_counter++], &result);
                final = (int *) result;
                *(*(mat3 + x) + y) = final;
            }

        printf("\nMatrix A :\n");
        printMatrix(mat1, r1, c1);
        printf("\nMatrix B :\n");
        printMatrix(mat2, r2, c2);
        printf("\nResultant Matrix C :\n");
        printMatrix(mat3, r1, c2);

        deallocateMemory(mat1,r1,mat2,r2,mat3,r1,threadID);

    } else
        printf("Matrix multiplication not possible\n");

    return 0;
}

/*OUTPUT*/
/*
sanul@sanul-HP-Notebook:~/CLionProjects/multithread_matrix$ ./a.out
Enter the number of row and col for matrix 1
2
3
Enter the number of row and col for matrix 2
3
2
Enter elements for matrix 1
1
1
1
1
1
1
Enter elements for matrix 2
1
1
1
1
1
1

Thread created count -> 0

Thread created count -> 1
Thread in execution with Thread ID : 139923076720384

Thread created count -> 2
Thread in execution with Thread ID : 139923068327680

Thread created count -> 3
Thread in execution with Thread ID : 139923059934976
Thread in execution with Thread ID : 139923051542272

Matrix A :


1  1  1
1  1  1

Matrix B :


1  1
1  1
1  1

Resultant Matrix C :


3  3
3  3
sanul@sanul-HP-Notebook:~/CLionProjects/multithread_matrix$

 */


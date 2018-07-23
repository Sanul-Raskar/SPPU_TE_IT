/*
Sanul Raskar
TE IT A2
331059
*/

/*
Note: create object file of binarySearch.c with the name binarySearch
eg. $ gcc -o binarySearch binarySearch.c

Then compile main.c and run it
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void bubbleSort(int arr[], int n);
void swap(int *xp, int *yp);
void accept();
void display();
char *intArray_to_String();
int number[10], n;

void accept()
{
  printf("How many numbers you want to sort? (Max 10)\n");
  scanf("%d", &n);
  printf("Enter the numbers to be sorted\n");
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &number[i]);
  }
}

void bubbleSort(int arr[], int n)
{
  int i, j;
  for (i = 0; i < n - 1; i++)
    for (j = 0; j < n - i - 1; j++)
      if (number[j] > number[j + 1])
        swap(&number[j], &number[j + 1]);
}

void swap(int *xp, int *yp)
{
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

void display()
{
  for (int i = 0; i < n; i++)
    printf("%d, ", number[i]);

  printf("\n");
}

char *intArray_to_String()
{
  int num = 0;
  char temp[] = {" "};
  char *buffer = (char *)malloc(24 * sizeof(char));

  for (int i = 0; i < n; i++)
  {
    num += sprintf(&buffer[num], "%d", number[i]);
    strcat(buffer, temp);
    num++;
  }
  buffer[num] = '\0';
  return buffer;
}

int main()
{
  pid_t cpid;
  char *argv[5], *outputString;
  int status = 500;
  accept();
  bubbleSort(number, n);
  display();
  outputString = intArray_to_String();
  argv[0] = outputString;
  argv[1] = NULL;
  cpid = fork();

  if (cpid == -1)
    printf("Error");
  else if (cpid == 0)
  {
    execve("./binarySearch", argv, NULL);
    printf("Error: Failed to execute another program\n");
  }
  else
    wait(NULL);
  return 0;
}

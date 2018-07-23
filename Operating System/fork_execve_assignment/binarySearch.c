/*
Sanul Raskar
TE IT A2
331059
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int binarySearch(int *arr, int l, int r, int x);
int *string_to_intArray();
int no;
int binarySearch(int *arr, int l, int r, int x)
{
  if (r >= l)
  {
    int mid = l + (r - l) / 2;
    if (arr[mid] == x)
      return mid;

    if (arr[mid] > x)
      return binarySearch(arr, l, mid - 1, x);
    return binarySearch(arr, mid + 1, r, x);
  }
  return -1;
}

int *string_to_intArray(char *str)
{
  int *arr = (int *)calloc(20, sizeof(int));
  const char s[2] = " ";
  char *token;
  int temp, i = 0;

  token = strtok(str, s);
  while (token != NULL)
  {
    temp = atoi(token);
    arr[i] = temp;
    i++;
    token = strtok(NULL, " ");
  }
  no = i;
  return arr;
}

int main(int argc, char *argv[])
{
  int key, count, flag, *array;

  printf("Accepted String by Second Program : %s\n", argv[0]);
  array = string_to_intArray(argv[0]);

  printf("Integer Array: ");
  for (int i = 0; i < no; i++)
  {
    printf("%d,", array[i]);
  }
  printf("\n");

  printf("Enter the number you want to search\n");
  scanf("%d", &key);

  flag = binarySearch(array, 0, no, key);
  if (flag == -1)
    printf("Number not found\n");
  else
    printf("Number Found at location [%d] \n", flag);
  return 0;
}

#include <time.h>

#include <stdlib.h>

#include <stdio.h>

int extraMemoryAllocated;

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void swap(int *a, int *b) {
  int tempvar = *a;
  *a = *b;
  *b = tempvar;
}

void heapify(int arr[], int n, int i) {
  // Finding the greatest among root, leftSide child, and rightSide child of the
  // tree
  int greatest = i;
  int leftSide = 2 * i + 1;
  int rightSide = 2 * i + 2;

  if (leftSide < n && arr[leftSide] > arr[greatest])
    greatest = leftSide;

  if (rightSide < n && arr[rightSide] > arr[greatest])
    greatest = rightSide;

  // Swap and continue heapifying if the root is not the greatest
  if (greatest != i) {
    swap(&arr[i], &arr[greatest]);
    heapify(arr, n, greatest);
  }
}


void heapSort(int arr[], int n) {
  // Build max heap
  for (int i = n / 2 - 1; i >= 0; i--)
    heapify(arr, n, i);

  for (int i = n - 1; i >= 0; i--) {
    swap(&arr[0], &arr[i]);

    heapify(arr, i, 0);
  }
}
void merge(int arr[], int left, int mid, int right)
{
    int i, j, k;
    int s1 = mid - left + 1;
    int s2 = right - mid;
 
    /* It will create two temporary arrays */
    int left_arr[s1], right_arr[s2];
 
    /* It will copy data from arr to temporary arrays */
    for (i = 0; i < s1; i++)
        left_arr[i] = arr[left + i];
   
    for (j = 0; j < s2; j++)
        right_arr[j] = arr[mid + 1 + j];
 
   
    i = 0, j = 0;  
    k = left;
    while (i < s1 && j < s2) {
        if (left_arr[i] <= right_arr[j]) {
            arr[k] = left_arr[i];
            i++;
        }
        else {
            arr[k] = right_arr[j];
            j++;
        }
        k++;
    }
 
    /* Copying the items of left_arr[] that have been left */
    while (i < s1) {
        arr[k] = left_arr[i];
        i++;
        k++;
    }
 
    /* Copying the items of right_arr[] that have been left */
    while (j < s2) {
        arr[k] = right_arr[j];
        j++;
        k++;
    }
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r) {
   if (l < r) {
       
        // finding the mid value of the array.
        int mid = l + (r - l) / 2;
 
        // Calling the merge sort for the first half
        mergeSort(pData, l, mid);
       
        // Calling the merge sort for the second half
        mergeSort(pData, mid + 1, r);
 
        // Calling the merge function
        merge(pData, l, mid, r);
    }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData) {
  FILE *inFile = fopen(inputFileName, "r");
  int dataSz = 0;
  int i, n, *data;
  *ppData = NULL;

  if (inFile) {
    fscanf(inFile, "%d\n", &dataSz);
    *ppData = (int *)malloc(sizeof(int) * dataSz);
    // Implement parse data block
    if (*ppData == NULL) {
      printf("Cannot allocate memory\n");
      exit(-1);
    }
    for (i = 0; i < dataSz; ++i) {
      fscanf(inFile, "%d ", &n);
      data = *ppData + i;
      *data = n;
    }

    fclose(inFile);
  }

  return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz) {
  int i, sz = dataSz - 100;
  printf("\tData:\n\t");
  for (i = 0; i < 100; ++i) {
    printf("%d ", pData[i]);
  }
  printf("\n\t");

  for (i = sz; i < dataSz; ++i) {
    printf("%d ", pData[i]);
  }
  printf("\n\n");
}

int main(void) {
  clock_t start, end;
  int i;
  double cpu_time_used;
  char *fileNames[] = {"input1.txt", "input2.txt", "input3.txt", "input4.txt"};

  for (i = 0; i < 4; ++i) {
    int *pDataSrc, *pDataCopy;
    int dataSz = parseData(fileNames[i], &pDataSrc);

    if (dataSz <= 0)
      continue;

    pDataCopy = (int *)malloc(sizeof(int) * dataSz);

    printf("---------------------------\n");
    printf("Dataset Size : %d\n", dataSz);
    printf("---------------------------\n");

    printf("Heap Sort:\n");
    memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
    extraMemoryAllocated = 0;
    start = clock();
    heapSort(pDataCopy, dataSz);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
    printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
    printArray(pDataCopy, dataSz);

    printf("Merge Sort:\n");
    memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
    extraMemoryAllocated = 0;
    start = clock();
    mergeSort(pDataCopy, 0, dataSz - 1);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
    printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
    printArray(pDataCopy, dataSz);

    free(pDataCopy);
    free(pDataSrc);
  }
}
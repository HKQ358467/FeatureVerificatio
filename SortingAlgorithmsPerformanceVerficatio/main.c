#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 冒泡排序
void bubbleSort(int arr[], int n) {
    if (arr == NULL || n <= 0) {
        printf("Invalid input for bubble sort.\n");
        return;
    }

    int i, j, temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// 选择排序
void selectionSort(int arr[], int n) {
    if (arr == NULL || n <= 0) {
        printf("Invalid input for selection sort.\n");
        return;
    }

    int i, j, min_idx, temp;
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

// 插入排序
void insertionSort(int arr[], int n) {
    if (arr == NULL || n <= 0) {
        printf("Invalid input for insertion sort.\n");
        return;
    }

    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high- 1; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++;    // increment index of smaller element
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

// 快速排序
void quickSort(int arr[], int low, int high) {
    if (arr == NULL || high < low) {
        printf("Invalid input for quick sort.\n");
        return;
    }

    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int arr[1000], n = sizeof(arr)/sizeof(arr[0]);
    clock_t start, end;
    double cpu_time_used;

    // 生成随机数组
    for(int i = 0; i < n; i++)
        arr[i] = rand() % 1000;

    // 冒泡排序
    start = clock();
    bubbleSort(arr, n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Bubble Sort time = %f\n", cpu_time_used);

    // 选择排序
    start = clock();
    selectionSort(arr, n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Selection Sort time = %f\n", cpu_time_used);

    // 插入排序
    start = clock();
    insertionSort(arr, n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Insertion Sort time = %f\n", cpu_time_used);

    // 快速排序
    start = clock();
    quickSort(arr, 0, n-1);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Quick Sort time = %f\n", cpu_time_used);

    return 0;
}
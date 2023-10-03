#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void triABulles(int arr[], int n) {
    int temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


void triParSelection(int arr[], int n) {
    int minIndex, temp;
    for (int i = 0; i < n - 1; i++) {
        minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

void triParInsertion(int arr[], int n) {
    int i, j, key;
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

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void triRapide(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        triRapide(arr, low, pi - 1);
        triRapide(arr, pi + 1, high);
    }
}


int main() {
    int sizes[] = {100, 1000, 10000, 100000};
    for (long unsigned int k = 0; k < sizeof(sizes) / sizeof(sizes[0]); k++) {

        int n = sizes[k];
        int arr[n];

        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 1000; 
        }

        printf("Mehdi : tp2 %d\n", n);

        clock_t debut, fin;

        int insertionArr[n];
        for (int i = 0; i < n; i++) {
            insertionArr[i] = arr[i];
        }
        debut = clock();
        triParInsertion(insertionArr, n);
        fin = clock();
        printf("Tri insertion\t taille %d\t temps %ld\n", n, (long)(fin - debut));

        int bubbleArr[n];
        for (int i = 0; i < n; i++) {
            bubbleArr[i] = arr[i];
        }
        debut = clock();
        triABulles(bubbleArr, n);
        fin = clock();
        printf("Tri bulles\t taille %d\t temps %ld\n", n, (long)(fin - debut));

        int selectionArr[n];
        for (int i = 0; i < n; i++) {
            insertionArr[i] = arr[i];
        }
        debut = clock();
        triParSelection(selectionArr, n);
        fin = clock();
        printf("Tri insertion\t taille %d\t temps %ld\n", n, (long)(fin - debut));

        int quickArr[n];
        for (int i = 0; i < n; i++) {
            quickArr[i] = arr[i];
        }
        debut = clock();
        triRapide(quickArr, 0, n - 1);
        fin = clock();
        printf("Quicksort\t taille %d\t temps %ld\n", n, (long)(fin - debut));
    }

    return 0;
}

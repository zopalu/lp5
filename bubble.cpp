#include <iostream>
#include <omp.h>

using namespace std;

void sequential_bubble_sort(int arr[], int size) {
    double start = omp_get_wtime();
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
    double end = omp_get_wtime();
    cout << "Sequential Bubble Sort:\n";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "Time Required: " << end - start << endl;
}

void parallel_bubble_sort(int arr[], int size) {
    double start = omp_get_wtime();
    for (int i = 0; i < size; i++) {
        if (i % 2 == 0) {
            #pragma omp parallel for
            for (int j = 0; j < size - 1; j += 2) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        } else {
            #pragma omp parallel for
            for (int j = 1; j < size - 1; j += 2) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
    double end = omp_get_wtime();
    cout << "Parallel Bubble Sort:\n";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "Time Required: " << end - start << endl;
}

int main() {
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;

    int array[size];

    cout << "Enter " << size << " integers: ";
    for (int i = 0; i < size; i++) {
        cin >> array[i];
    }

    sequential_bubble_sort(array, size);

    int parallel_array[size];
    for (int i = 0; i < size; i++) {
        parallel_array[i] = array[i];
    }
    parallel_bubble_sort(parallel_array, size);

    return 0;
}

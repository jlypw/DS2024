#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

// Bubble Sort
void bubbleSort(vector<int>& arr) {
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        for (size_t j = 0; j < arr.size() - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Insertion Sort
void insertionSort(vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        size_t j = i;
        while (j > 0 && arr[j - 1] > key) {
            arr[j] = arr[j - 1];
            --j;
        }
        arr[j] = key;
    }
}

// Selection Sort
void selectionSort(vector<int>& arr) {
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

// Merge Sort
void merge(vector<int>& arr, size_t left, size_t mid, size_t right) {
    vector<int> temp(right - left + 1);
    size_t i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (size_t p = 0; p < temp.size(); ++p) {
        arr[left + p] = temp[p];
    }
}

void mergeSort(vector<int>& arr, size_t left, size_t right) {
    if (left < right) {
        size_t mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Quick Sort
size_t partition(vector<int>& arr, size_t left, size_t right) {
    int pivot = arr[right];
    size_t i = left;
    for (size_t j = left; j < right; ++j) {
        if (arr[j] <= pivot) {
            swap(arr[i++], arr[j]);
        }
    }
    swap(arr[i], arr[right]);
    return i;
}

void quickSort(vector<int>& arr, size_t left, size_t right) {
    if (left < right) {
        size_t pi = partition(arr, left, right);
        if (pi > 0) quickSort(arr, left, pi - 1);  // Avoid underflow
        quickSort(arr, pi + 1, right);
    }
}

// Heap Sort
void heapify(vector<int>& arr, size_t n, size_t i) {
    size_t largest = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    size_t n = arr.size();
    for (size_t i = n / 2 - 1; i < n; --i) {
        heapify(arr, n, i);
    }

    for (size_t i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Test Function
void testSorting(void (*sortFunc)(vector<int>&), const string& sortName, vector<int> arr) {
    clock_t start = clock();
    sortFunc(arr);
    clock_t end = clock();
    cout << sortName << " took " << (double)(end - start) / CLOCKS_PER_SEC << " seconds.\n";
}

// Main Function
int main() {
    const size_t N = 10000;
    vector<int> sortedArr(N), reversedArr(N), randomArr(N);

    for (size_t i = 0; i < N; ++i) {
        sortedArr[i] = i;
        reversedArr[i] = N - i;
        randomArr[i] = rand() % N;
    }

    cout << "Testing Sorting Algorithms:\n\n";

    testSorting(bubbleSort, "Bubble Sort", sortedArr);
    testSorting(bubbleSort, "Bubble Sort", reversedArr);
    testSorting(bubbleSort, "Bubble Sort", randomArr);

    testSorting(insertionSort, "Insertion Sort", sortedArr);
    testSorting(insertionSort, "Insertion Sort", reversedArr);
    testSorting(insertionSort, "Insertion Sort", randomArr);

    testSorting(selectionSort, "Selection Sort", sortedArr);
    testSorting(selectionSort, "Selection Sort", reversedArr);
    testSorting(selectionSort, "Selection Sort", randomArr);

    testSorting([](vector<int>& arr) { mergeSort(arr, 0, arr.size() - 1); }, "Merge Sort", sortedArr);
    testSorting([](vector<int>& arr) { mergeSort(arr, 0, arr.size() - 1); }, "Merge Sort", reversedArr);
    testSorting([](vector<int>& arr) { mergeSort(arr, 0, arr.size() - 1); }, "Merge Sort", randomArr);

    testSorting([](vector<int>& arr) { quickSort(arr, 0, arr.size() - 1); }, "Quick Sort", sortedArr);
    testSorting([](vector<int>& arr) { quickSort(arr, 0, arr.size() - 1); }, "Quick Sort", reversedArr);
    testSorting([](vector<int>& arr) { quickSort(arr, 0, arr.size() - 1); }, "Quick Sort", randomArr);

    testSorting(heapSort, "Heap Sort", sortedArr);
    testSorting(heapSort, "Heap Sort", reversedArr);
    testSorting(heapSort, "Heap Sort", randomArr);

    return 0;
}


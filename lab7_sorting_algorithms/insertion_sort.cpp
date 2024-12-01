#include <span>

void insertionSort(std::span<int> arr, long long& comparisons, long long& swaps) {
    size_t n = arr.size();
    for (size_t i = 1; i < n; ++i) {
        int key = arr[i];
        size_t j = i;
        while (j > 0) {
            ++comparisons;
            if (arr[j - 1] <= key) break;
            arr[j] = arr[j - 1];
            ++swaps;
            --j;
        }
        arr[j] = key;
        ++swaps;
    }
}


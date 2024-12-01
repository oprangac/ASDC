#include <span>
#include <utility>

void bubbleSort(std::span<int> arr, long long& comparisons, long long& swaps) {
    size_t n = arr.size();
    for (size_t i = 0; i < n - 1; ++i) {
        for (size_t j = 0; j < n - i - 1; ++j) {
            ++comparisons;
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                ++swaps;
            }
        }
    }
}

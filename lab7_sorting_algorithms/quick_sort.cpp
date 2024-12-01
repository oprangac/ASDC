#include <span>
#include <utility>

void quickSort(std::span<int> arr, long long& comparisons, long long& swaps) {
    if (arr.size() <= 1) return;

    int pivot = arr[arr.size() / 2];
    size_t left = 0, right = arr.size() - 1;

    while (left <= right) {
        while (arr[left] < pivot) {
            ++comparisons;
            ++left;
        }
        while (arr[right] > pivot) {
            ++comparisons;
            --right;
        }
        if (left <= right) {
            std::swap(arr[left], arr[right]);
            ++swaps;
            ++left;
            --right;
        }
    }

    if (right > 0) quickSort(arr.subspan(0, right + 1), comparisons, swaps);
    quickSort(arr.subspan(left), comparisons, swaps);
}


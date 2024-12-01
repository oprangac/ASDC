#include <vector>
#include <span>

std::vector<int> mergeSort(std::span<int> arr, long long& comparisons, long long& copies) {
    if (arr.size() <= 1) {
        return {arr.begin(), arr.end()};
    }
    
    size_t mid = arr.size() / 2;
    auto left = mergeSort(arr.subspan(0, mid), comparisons, copies);
    auto right = mergeSort(arr.subspan(mid), comparisons, copies);
    
    std::vector<int> merged;
    size_t i = 0, j = 0;
    while (i < left.size() && j < right.size()) {
        ++comparisons;
        if (left[i] <= right[j]) {
            merged.push_back(left[i++]);
            ++copies;
        } else {
            merged.push_back(right[j++]);
            ++copies;
        }
    }
    while (i < left.size()) {
        merged.push_back(left[i++]);
        ++copies;
    }
    while (j < right.size()) {
        merged.push_back(right[j++]);
        ++copies;
    }
    
    return merged;
}


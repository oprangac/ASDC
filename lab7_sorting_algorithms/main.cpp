#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "bubble_sort.cpp"
#include "insertion_sort.cpp"
#include "merge_sort.cpp"
#include "quick_sort.cpp"
#include <map>

struct SortResult {
    std::string algorithm;
    int arraySize;
    std::string arrayType;
    int timeMicroseconds;
    long long comparisons;
    long long swapsOrCopies;
};

void generateRandomArray(std::vector<int>& arr, int size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 1000);
    arr.resize(size);
    for (int& elem : arr) {
        elem = dist(gen);
    }
}

void generateSortedArray(std::vector<int>& arr, int size) {
    arr.resize(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = i;
    }
}

void generateReverseSortedArray(std::vector<int>& arr, int size) {
    arr.resize(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = size - i;
    }
}

void testSortAlgorithm(const std::string& name, void (*sortFunc)(std::span<int>, long long&, long long&), std::vector<int>& arr, const std::string& arrayType, int size, std::vector<SortResult>& results)
{
    auto copy = arr;
    long long comparisons = 0, swaps = 0;

    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(copy, comparisons, swaps);
    auto end = std::chrono::high_resolution_clock::now();

    /*std::cout << name << " - Execution time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " microseconds\n";
    std::cout << "Comparisons: " << comparisons << ", Swaps: " << swaps << "\n";*/

    int time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    results.push_back({name, size, arrayType, time, comparisons, swaps});
}

void testMergeSort(const std::string& name, std::vector<int> (*sortFunc)(std::span<int>, long long&, long long&), std::vector<int>& arr, const std::string& arrayType, int size, std::vector<SortResult>& results)
{
    auto copy = arr;
    long long comparisons = 0, copies = 0;

    auto start = std::chrono::high_resolution_clock::now();
    auto sorted = sortFunc(copy, comparisons, copies);
    auto end = std::chrono::high_resolution_clock::now();

    /*std::cout << name << " - Execution time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " microseconds\n";
    std::cout << "Comparisons: " << comparisons << ", Copies: " << copies << "\n";*/

    int time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    results.push_back({name, size, arrayType, time, comparisons, copies});
}

void analyzeAverageExecutionTime(const std::vector<SortResult>& results) {
    std::map<std::string, std::map<int, double>> averageTimes;

    for (const auto& result : results) {
        averageTimes[result.algorithm][result.arraySize] += result.timeMicroseconds;
    }

    for (auto& [algorithm, sizeMap] : averageTimes) {
        for (auto& [size, totalTime] : sizeMap) {
            totalTime /= 3.0; // 3 types of arrays
        }
    }

    std::cout << "\nAverage Execution Times (microseconds):\n";
    for (const auto& [algorithm, sizeMap] : averageTimes) {
        std::cout << "Algorithm: " << algorithm << "\n";
        for (const auto& [size, avgTime] : sizeMap) {
            std::cout << "  Size: " << size << ", Average Time: " << avgTime << " µs\n";
        }
        std::cout << "----------------------------------------------------------\n";
    }
}

int main() {
    std::vector<int> arr;
    std::vector<SortResult> results;

    std::vector<int> sizes = {1000, 10000, 100000};
    std::vector<std::string> types = {"Random", "Sorted", "Reverse Sorted"};

    for (int size : sizes) {
    std::cout << "\nResults for Array Size: " << size << "\n";

    for (const auto& type : types) {
        if (type == "Random") generateRandomArray(arr, size);
        else if (type == "Sorted") generateSortedArray(arr, size);
        else if (type == "Reverse Sorted") generateReverseSortedArray(arr, size);

        testSortAlgorithm("Bubble Sort", bubbleSort, arr, type, size, results);
        testSortAlgorithm("Insertion Sort", insertionSort, arr, type, size, results);
        testMergeSort("Merge Sort", mergeSort, arr, type, size, results);
        testSortAlgorithm("Quick Sort", quickSort, arr, type, size, results);

        for (const auto& result : results) {
            if (result.arraySize == size && result.arrayType == type) {
                std::cout << "Algorithm: " << result.algorithm
                          << ", Type: " << result.arrayType
                          << ", Time: " << result.timeMicroseconds << " µs"
                          << ", Comparisons: " << result.comparisons
                          << ", Swaps/Copies: " << result.swapsOrCopies << "\n";
            }
        }

        std::cout << "----------------------------------------------------------" << "\n";
    }
}

    analyzeAverageExecutionTime(results);

    return 0;
}

/*
Results for Array Size: 1000
Algorithm: Bubble Sort, Type: Random, Time: 2705 µs, Comparisons: 499500, Swaps/Copies: 246638
Algorithm: Insertion Sort, Type: Random, Time: 851 µs, Comparisons: 247631, Swaps/Copies: 247637
Algorithm: Merge Sort, Type: Random, Time: 1184 µs, Comparisons: 8729, Swaps/Copies: 9976
Algorithm: Quick Sort, Type: Random, Time: 94 µs, Comparisons: 7822, Swaps/Copies: 2672
----------------------------------------------------------
Algorithm: Bubble Sort, Type: Sorted, Time: 1188 µs, Comparisons: 499500, Swaps/Copies: 0
Algorithm: Insertion Sort, Type: Sorted, Time: 3 µs, Comparisons: 999, Swaps/Copies: 999
Algorithm: Merge Sort, Type: Sorted, Time: 1064 µs, Comparisons: 4932, Swaps/Copies: 9976
Algorithm: Quick Sort, Type: Sorted, Time: 26 µs, Comparisons: 7987, Swaps/Copies: 511
----------------------------------------------------------
Algorithm: Bubble Sort, Type: Reverse Sorted, Time: 3591 µs, Comparisons: 499500, Swaps/Copies: 499500
Algorithm: Insertion Sort, Type: Reverse Sorted, Time: 1709 µs, Comparisons: 499500, Swaps/Copies: 500499
Algorithm: Merge Sort, Type: Reverse Sorted, Time: 1093 µs, Comparisons: 5044, Swaps/Copies: 9976
Algorithm: Quick Sort, Type: Reverse Sorted, Time: 29 µs, Comparisons: 6996, Swaps/Copies: 1010
----------------------------------------------------------

Results for Array Size: 10000
Algorithm: Bubble Sort, Type: Random, Time: 286431 µs, Comparisons: 49995000, Swaps/Copies: 25027350
Algorithm: Insertion Sort, Type: Random, Time: 84993 µs, Comparisons: 25037338, Swaps/Copies: 25037349
Algorithm: Merge Sort, Type: Random, Time: 12533 µs, Comparisons: 120544, Swaps/Copies: 133616
Algorithm: Quick Sort, Type: Random, Time: 972 µs, Comparisons: 86519, Swaps/Copies: 38633
----------------------------------------------------------
Algorithm: Bubble Sort, Type: Sorted, Time: 117040 µs, Comparisons: 49995000, Swaps/Copies: 0
Algorithm: Insertion Sort, Type: Sorted, Time: 38 µs, Comparisons: 9999, Swaps/Copies: 9999
Algorithm: Merge Sort, Type: Sorted, Time: 11690 µs, Comparisons: 64608, Swaps/Copies: 133616
Algorithm: Quick Sort, Type: Sorted, Time: 332 µs, Comparisons: 113631, Swaps/Copies: 5904
----------------------------------------------------------
Algorithm: Bubble Sort, Type: Reverse Sorted, Time: 362300 µs, Comparisons: 49995000, Swaps/Copies: 49995000
Algorithm: Insertion Sort, Type: Reverse Sorted, Time: 169144 µs, Comparisons: 49995000, Swaps/Copies: 50004999
Algorithm: Merge Sort, Type: Reverse Sorted, Time: 11594 µs, Comparisons: 69008, Swaps/Copies: 133616
Algorithm: Quick Sort, Type: Reverse Sorted, Time: 354 µs, Comparisons: 103644, Swaps/Copies: 10904
----------------------------------------------------------

Results for Array Size: 100000
Algorithm: Bubble Sort, Type: Random, Time: 33388078 µs, Comparisons: 4999950000, Swaps/Copies: 2497218790
Algorithm: Insertion Sort, Type: Random, Time: 8534538 µs, Comparisons: 2497318783, Swaps/Copies: 2497318789
Algorithm: Merge Sort, Type: Random, Time: 145802 µs, Comparisons: 1535827, Swaps/Copies: 1668928
Algorithm: Quick Sort, Type: Random, Time: 10953 µs, Comparisons: 1015899, Swaps/Copies: 531996
----------------------------------------------------------
Algorithm: Bubble Sort, Type: Sorted, Time: 12259826 µs, Comparisons: 4999950000, Swaps/Copies: 0
Algorithm: Insertion Sort, Type: Sorted, Time: 380 µs, Comparisons: 99999, Swaps/Copies: 99999
Algorithm: Merge Sort, Type: Sorted, Time: 118040 µs, Comparisons: 815024, Swaps/Copies: 1668928
Algorithm: Quick Sort, Type: Sorted, Time: 3843 µs, Comparisons: 1468946, Swaps/Copies: 65535
----------------------------------------------------------
Algorithm: Bubble Sort, Type: Reverse Sorted, Time: 36713192 µs, Comparisons: 4999950000, Swaps/Copies: 4999950000
Algorithm: Insertion Sort, Type: Reverse Sorted, Time: 17299008 µs, Comparisons: 4999950000, Swaps/Copies: 5000049999
Algorithm: Merge Sort, Type: Reverse Sorted, Time: 117141 µs, Comparisons: 853904, Swaps/Copies: 1668928
Algorithm: Quick Sort, Type: Reverse Sorted, Time: 4150 µs, Comparisons: 1368962, Swaps/Copies: 115534
----------------------------------------------------------


Average Execution Times (microseconds):
Average Execution Times (microseconds):
Algorithm: Bubble Sort
Algorithm: Bubble Sort
  Size: 1000, Average Time: 2494.67 µs
  Size: 1000, Average Time: 2494.67 µs
  Size: 10000, Average Time: 255257 µs
  Size: 100000, Average Time: 2.74537e+07 µs
----------------------------------------------------------
  Size: 100000, Average Time: 2.74537e+07 µs
----------------------------------------------------------
Algorithm: Insertion Sort
Algorithm: Insertion Sort
  Size: 1000, Average Time: 854.333 µs
  Size: 10000, Average Time: 84725 µs
  Size: 100000, Average Time: 8.61131e+06 µs
----------------------------------------------------------
Algorithm: Merge Sort
  Size: 1000, Average Time: 1113.67 µs
  Size: 10000, Average Time: 11939 µs
  Size: 100000, Average Time: 126994 µs
----------------------------------------------------------
Algorithm: Quick Sort
  Size: 1000, Average Time: 49.6667 µs
  Size: 10000, Average Time: 552.667 µs
  Size: 100000, Average Time: 6315.33 µs
----------------------------------------------------------
*/

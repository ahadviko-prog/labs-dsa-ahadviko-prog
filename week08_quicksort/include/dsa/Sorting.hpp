//
// Created by marius on 2/19/26.
//

#pragma once
#include <cstddef>

namespace dsa {

    // Lomuto partition scheme
    // Pivot = arr[high]
    template <class T>
    int partition(T* arr, int low, int high) {
        T pivot = arr[high];

        int i = low - 1;

        for (int j = low; j < high; ++j) {
            if (arr[j] <= pivot) {
                ++i;

                T temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        T temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;

        return i + 1;
    }

    template <class T>
    void quicksort(T* arr, int low, int high) {
        if (low >= high) {
            return;
        }

        int pivotIndex = partition(arr, low, high);

        quicksort(arr, low, pivotIndex - 1);
        quicksort(arr, pivotIndex + 1, high);
    }

    // Convenience overload for raw arrays
    template <class T>
    void quicksort(T* arr, std::size_t n) {
        if (n < 2) return;
        quicksort(arr, 0, static_cast<int>(n) - 1);
    }

} // namespace dsa
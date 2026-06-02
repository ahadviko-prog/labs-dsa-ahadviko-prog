//
// Created by marius on 2/19/26.
//

#pragma once
#include <utility>

namespace dsa {

    // heapify_down: fixes heap property in arr[0..n-1] starting at i
    template <class T>
    void heapify_down(T* arr, int n, int i) {

        while (true) {
            int largest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < n && arr[left] > arr[largest])
                largest = left;

            if (right < n && arr[right] > arr[largest])
                largest = right;

            if (largest == i)
                break;

            std::swap(arr[i], arr[largest]);
            i = largest;
        }
    }

    // build_heap: bottom-up O(n)
    template <class T>
    void build_heap(T* arr, int n) {

        for (int i = n / 2 - 1; i >= 0; --i) {
            heapify_down(arr, n, i);
        }
    }

    // heapsort: O(n log n)
    template <class T>
    void heapsort(T* arr, int n) {

        build_heap(arr, n);

        for (int end = n - 1; end > 0; --end) {
            std::swap(arr[0], arr[end]);
            heapify_down(arr, end, 0);
        }
    }

} // namespace dsa
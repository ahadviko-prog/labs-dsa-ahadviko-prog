#pragma once
#include <cstddef>

namespace dsa {

    struct SortStats {
        std::size_t comparisons = 0;
        std::size_t swaps = 0;
    };

    // Bubble Sort
    template <class T>
    SortStats bubble_sort(T* a, std::size_t n) {
        SortStats st;

        if (n < 2) {
            return st;
        }

        for (std::size_t i = 0; i < n - 1; ++i) {
            bool swapped = false;

            for (std::size_t j = 0; j < n - 1 - i; ++j) {
                ++st.comparisons;

                if (a[j] > a[j + 1]) {
                    T temp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = temp;

                    ++st.swaps;
                    swapped = true;
                }
            }

            if (!swapped) {
                break;
            }
        }

        return st;
    }

    // Shell Sort using gaps n/2, n/4, ..., 1
    template <class T>
    SortStats shell_sort(T* a, std::size_t n) {
        SortStats st;

        for (std::size_t gap = n / 2; gap > 0; gap /= 2) {

            for (std::size_t i = gap; i < n; ++i) {

                T temp = a[i];
                std::size_t j = i;
                bool moved = false;

                while (j >= gap) {
                    ++st.comparisons;

                    if (a[j - gap] > temp) {
                        a[j] = a[j - gap];
                        ++st.swaps;      // count shift
                        j -= gap;
                        moved = true;
                    } else {
                        break;
                    }
                }

                if (moved) {
                    a[j] = temp;
                    ++st.swaps;          // count placement only if moved
                }
            }
        }

        return st;
    }

} // namespace dsa
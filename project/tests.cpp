#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "dsa/DynamicArray.hpp"
#include "dsa/Stack.hpp"
#include "dsa/Queue.hpp"
#include "dsa/LinkedList.hpp"
#include "dsa/BST.hpp"

// Re-declaring sorting algorithm logic for validation
template <typename T>
size_t partition(DynamicArray<T>& arr, int low, int high) {
    T pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            i++;
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

template <typename T>
void quickSort(DynamicArray<T>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ==========================================
// AUTOMATED UNIT TEST SUITES
// ==========================================

TEST_CASE("Testing Stack LIFO Functionality") {
    Stack<int> s;
    CHECK(s.isEmpty() == true);
    s.push(10);
    s.push(20);
    CHECK(s.size() == 2);
    CHECK(s.top() == 20);
    s.pop();
    CHECK(s.top() == 10);
}

TEST_CASE("Testing Queue FIFO Functionality") {
    Queue<int> q;
    CHECK(q.isEmpty() == true);
    q.enqueue(100);
    q.enqueue(200);
    CHECK(q.front() == 100);
    q.dequeue();
    CHECK(q.front() == 200);
}

TEST_CASE("Testing DynamicArray Structure") {
    DynamicArray<int> arr;
    CHECK(arr.size() == 0);
    arr.push_back(5);
    arr.push_back(15);
    CHECK(arr[0] == 5);
    CHECK(arr[1] == 15);
}

TEST_CASE("Testing LinkedList Mechanics") {
    LinkedList<int> list;
    list.append(1);
    list.append(2);
    CHECK(list.size() == 2);
}

TEST_CASE("Testing Custom Quicksort Implementation") {
    DynamicArray<int> arr;
    arr.push_back(30);
    arr.push_back(10);
    arr.push_back(20);

    quickSort(arr, 0, static_cast<int>(arr.size()) - 1);

    CHECK(arr[0] == 10);
    CHECK(arr[1] == 20);
    CHECK(arr[2] == 30);
}

TEST_CASE("Testing BST Struct and Insertion Order") {
    BST<int> bst;
    bst.insert(15);
    bst.insert(10);
    bst.insert(20);

    REQUIRE(bst.getRoot() != nullptr);
    CHECK(bst.getRoot()->data == 15);
    CHECK(bst.getRoot()->left->data == 10);
    CHECK(bst.getRoot()->right->data == 20);
}
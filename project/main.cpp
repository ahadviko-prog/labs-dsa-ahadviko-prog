#include <iostream>
#include "dsa/DynamicArray.hpp"
#include "dsa/Stack.hpp"
#include "dsa/Queue.hpp"
#include "dsa/LinkedList.hpp"
#include "dsa/BST.hpp"

// Algorithm 1: Quicksort
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

// Algorithm 2: DFS Traversal using custom Stack
template <typename T>
void iterativeDFS(const BST<T>& bst) {
    if (!bst.getRoot()) return;

    Stack<typename BST<T>::TreeNode*> stack;
    typename BST<T>::TreeNode* current = bst.getRoot();

    while (current != nullptr || !stack.isEmpty()) {
        while (current != nullptr) {
            stack.push(current);
            current = current->left;
        }
        current = stack.top();
        stack.pop();

        std::cout << current->data << " ";
        current = current->right;
    }
    std::cout << "\n";
}

int main() {
    int choice = 0;
    Stack<int> myStack;
    Queue<int> myQueue;
    LinkedList<int> myList;
    DynamicArray<int> myArr;
    BST<int> myBST;

    while (choice != 6) {
        std::cout << "\n===============================\n";
        std::cout << "      ALGORITHM PLAYGROUND     \n";
        std::cout << "===============================\n";
        std::cout << "1. Test Stack\n";
        std::cout << "2. Test Queue\n";
        std::cout << "3. Test Linked List\n";
        std::cout << "4. Sort Numbers (Quicksort + DynamicArray)\n";
        std::cout << "5. Traverse Tree (DFS + BST)\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter choice: ";

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Exiting.\n";
            break;
        }

        switch (choice) {
            case 1:
                std::cout << "\n--- Testing Stack ---\n";
                std::cout << "Pushing 50, 100 onto stack...\n";
                myStack.push(50);
                myStack.push(100);
                std::cout << "Stack Top: " << myStack.top() << "\n";
                break;
            case 2:
                std::cout << "\n--- Testing Queue ---\n";
                std::cout << "Enqueueing 500, 600...\n";
                myQueue.enqueue(500);
                myQueue.enqueue(600);
                std::cout << "Queue Front: " << myQueue.front() << "\n";
                break;
            case 3:
                std::cout << "\n--- Testing Linked List ---\n";
                std::cout << "Appending 7, 8 to list:\n";
                myList.append(7);
                myList.append(8);
                myList.display();
                break;
            case 4:
                std::cout << "\n--- Sorting Numbers (Quicksort) ---\n";
                myArr.clear();
                myArr.push_back(9);
                myArr.push_back(2);
                myArr.push_back(5);
                std::cout << "Original array elements: 9 2 5\n";
                quickSort(myArr, 0, static_cast<int>(myArr.size()) - 1);
                std::cout << "Sorted DynamicArray: " << myArr[0] << " " << myArr[1] << " " << myArr[2] << "\n";
                break;
            case 5:
                std::cout << "\n--- Tree Traversal (DFS) ---\n";
                myBST.insert(25);
                myBST.insert(15);
                myBST.insert(35);
                std::cout << "DFS In-Order Traversal Result: ";
                iterativeDFS(myBST);
                break;
            case 6:
                std::cout << "Exiting Playground. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
                break;
        }
    }
    return 0;
}
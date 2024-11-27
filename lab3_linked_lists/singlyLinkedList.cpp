#include <iostream>
#include <cassert>

template<typename T>
struct Node {
    T value;           // Data stored in the node
    Node* nextNode;    // Pointer to the next node in the list

    Node(T val) : value(val), nextNode(nullptr) {}
};

template<typename T>
struct LinkedList {
    Node<T>* firstNode;
    Node<T>* lastNode;
    int size;

    LinkedList() : firstNode(nullptr), lastNode(nullptr), size(0) {} 
};

template<typename T>
Node<T>* insertAfter(LinkedList<T>& list, Node<T>* node, T value) {
    Node<T>* newNode = new Node<T>(value);

    if (node == nullptr) {
        // Insert at the beginning
        newNode->nextNode = list.firstNode;
        list.firstNode = newNode;

        // If the list was empty, update the lastNode pointer
        if (list.lastNode == nullptr) {
            list.lastNode = newNode;
        }
    } else {
        // Insert after the given node
        newNode->nextNode = node->nextNode;
        node->nextNode = newNode;

        // If the given node was the last node, update the lastNode pointer
        if (node == list.lastNode) {
            list.lastNode = newNode;
        }
    }

    list.size++;
    return newNode;
}

template<typename T>
struct FindNodeResult {
    Node<T>* foundNode;
    Node<T>* prevNode;

    FindNodeResult(Node<T>* found = nullptr, Node<T>* prev = nullptr)
        : foundNode(found), prevNode(prev) {}
};

// find function
template<typename T>
FindNodeResult<T> find(LinkedList<T>& list, T value) {
    Node<T>* current = list.firstNode;
    Node<T>* previous = nullptr;

    while (current != nullptr) {
        if (current->value == value) {
            return FindNodeResult<T>(current, previous);
        }
        previous = current;
        current = current->nextNode;
    }

    return FindNodeResult<T>(nullptr, nullptr);
}

// removeAfter function
template<typename T>
void removeAfter(LinkedList<T>& list, Node<T>* node) {
    if (node == nullptr) {
        // Remove the first node
        if (list.firstNode == nullptr) {
            return;
        }

        Node<T>* nodeToRemove = list.firstNode;
        list.firstNode = list.firstNode->nextNode;

        // If we removed the last node, update the lastNode pointer
        if (list.firstNode == nullptr) {
            list.lastNode = nullptr;
        }

        delete nodeToRemove;
    } else {
        // Remove the node after the given node
        Node<T>* nodeToRemove = node->nextNode;
        if (nodeToRemove == nullptr) {
            return;
        }

        node->nextNode = nodeToRemove->nextNode;

        // If we removed the last node, update the lastNode pointer
        if (nodeToRemove == list.lastNode) {
            list.lastNode = node;
        }

        delete nodeToRemove; // Free the memory
    }

    list.size--;
}

// assertNoCycles function
template<typename T>
void assertNoCycles(LinkedList<T>& list) {
    Node<T>* current = list.firstNode;
    int count = 0;

    while (current != nullptr) {
        count++;
        if (count > list.size) {
            assert(false && "Cycle detected in the linked list!");
        }
        current = current->nextNode;
    }
}

int main() {
    LinkedList<int> list;

    // Test insertAfter
    Node<int>* first = new Node<int>(10);
    list.firstNode = first;
    list.lastNode = first;
    list.size++;

    insertAfter(list, first, 20);
    insertAfter(list, first, 15);

    // Test find
    FindNodeResult<int> result = find(list, 20);
    if (result.foundNode) {
        std::cout << "Found value: " << result.foundNode->value << "\n";
    } else {
        std::cout << "Value not found\n";
    }

    // Test removeAfter
    removeAfter(list, first); // Remove the node after 10 (should remove 15)

    // Test assertNoCycles
    assertNoCycles(list);

    // Print the list
    Node<int>* current = list.firstNode;
    while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->nextNode;
    }
    std::cout << "\n";

    return 0;
}

#include <iostream>
#include <cassert>

template<typename T>
struct Node {
    T value;
    Node* nextNode;
    Node* prevNode;

    Node(T val) : value(val), nextNode(nullptr), prevNode(nullptr) {}
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
        if (list.firstNode != nullptr) {
            list.firstNode->prevNode = newNode;
        }
        list.firstNode = newNode;

        // If the list was empty, update the lastNode pointer
        if (list.lastNode == nullptr) {
            list.lastNode = newNode;
        }
    } else {
        // Insert after the given node
        newNode->nextNode = node->nextNode;
        newNode->prevNode = node;
        if (node->nextNode != nullptr) {
            node->nextNode->prevNode = newNode;
        }
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
Node<T>* insertBefore(LinkedList<T>& list, Node<T>* node, T value) {
    Node<T>* newNode = new Node<T>(value);

    if (node == nullptr) {
        // Insert at the end
        newNode->prevNode = list.lastNode;
        if (list.lastNode != nullptr) {
            list.lastNode->nextNode = newNode;
        }
        list.lastNode = newNode;

        // If the list was empty, update the firstNode pointer
        if (list.firstNode == nullptr) {
            list.firstNode = newNode;
        }
    } else {
        // Insert before the given node
        newNode->prevNode = node->prevNode;
        newNode->nextNode = node;
        if (node->prevNode != nullptr) {
            node->prevNode->nextNode = newNode;
        }
        node->prevNode = newNode;

        // If the given node was the first node, update the firstNode pointer
        if (node == list.firstNode) {
            list.firstNode = newNode;
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

    while (current != nullptr) {
        if (current->value == value) {
            return FindNodeResult<T>(current, current->prevNode);
        }
        current = current->nextNode;
    }

    return FindNodeResult<T>(nullptr, nullptr);
}

template<typename T>
void remove(LinkedList<T>& list, Node<T>* node) {
    if (node == nullptr) {
        return;
    }

    if (node->prevNode != nullptr) {
        node->prevNode->nextNode = node->nextNode;
    } else {
        // Node is the first node
        list.firstNode = node->nextNode;
    }

    if (node->nextNode != nullptr) {
        node->nextNode->prevNode = node->prevNode;
    } else {
        // Node is the last node
        list.lastNode = node->prevNode;
    }

    delete node; // Free the memory
    list.size--;
}

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

    Node<int>* first = new Node<int>(10);
    list.firstNode = first;
    list.lastNode = first;
    list.size++;

    // insertAfter and insertBefore for subsequent operations
    Node<int>* second = insertAfter(list, first, 20);  // Insert 20 after 10
    insertAfter(list, first, 15);                     // Insert 15 after 10
    insertBefore(list, first, 5);                     // Insert 5 before 10
    insertBefore(list, list.lastNode, 25);            // Insert 25 before the last node

    // Test find
    auto result = find(list, 15);
    if (result.foundNode) {
        std::cout << "Found value: " << result.foundNode->value << "\n";
    } else {
        std::cout << "Value not found\n";
    }

    // Test remove
    remove(list, second); // Remove the node with value 20

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

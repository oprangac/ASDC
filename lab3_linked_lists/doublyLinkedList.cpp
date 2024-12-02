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
        newNode->nextNode = list.firstNode;
        if (list.firstNode != nullptr) {
            list.firstNode->prevNode = newNode;
        }
        list.firstNode = newNode;
    } else {
        newNode->nextNode = node->nextNode;
        newNode->prevNode = node;
        if (node->nextNode != nullptr) {
            node->nextNode->prevNode = newNode;
        }
        node->nextNode = newNode;
    }

    // If the list was empty or the given node was the last node, update the lastNode pointer
    if (list.lastNode == nullptr || node == list.lastNode) {
        list.lastNode = newNode;
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
Node<T>* insertFront(LinkedList<T>& list, T value) {
    return insertAfter(list, static_cast<Node<int>*>(nullptr), value);
}

template<typename T>
Node<T>* find(LinkedList<T>& list, T value) {
    Node<T>* current = list.firstNode;

    while (current != nullptr) {
        if (current->value == value) {
            return current;
        }
        current = current->nextNode;
    }

    return nullptr;
}

template<typename T>
void remove(LinkedList<T>& list, Node<T>* node) {
    assert(node != nullptr && "Node to be removed cannot be null");

    if (node->prevNode != nullptr) {
        node->prevNode->nextNode = node->nextNode;
    } else {
        list.firstNode = node->nextNode;
    }

    if (node->nextNode != nullptr) {
        node->nextNode->prevNode = node->prevNode;
    } else {
        list.lastNode = node->prevNode;
    }

    delete node;
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

    Node<int>* first = insertFront(list, 10);
    Node<int>* second = insertAfter(list, first, 5);
    insertAfter(list, second, 20);
    insertBefore(list, first, 15);

    Node<int>* result = find(list, 10);
    assert(result != nullptr && "Cannot find node with this value");
    std::cout << "Found value: " << result->value << "\n";
    assert(result->prevNode != nullptr && "prev node is null");
    std::cout << "Previous node to found node: " << result->prevNode->value << "\n";
    
    remove(list, first);

    assertNoCycles(list);

    Node<int>* current = list.firstNode;
    while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->nextNode;
    }
    std::cout << "\n";

    return 0;
}

#include <iostream>
#include <cassert>

template<typename T>
struct Node {
    T value;
    Node* nextNode;

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
        newNode->nextNode = list.firstNode;
        list.firstNode = newNode;

    } else {
        newNode->nextNode = node->nextNode;
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
Node<T>* insertFront(LinkedList<T>& list, T value) {
    return insertAfter(list, static_cast<Node<int>*>(nullptr), value);
}

template<typename T>
struct FindNodeResult {
    Node<T>* foundNode;
    Node<T>* prevNode;

    FindNodeResult(Node<T>* found = nullptr, Node<T>* prev = nullptr)
        : foundNode(found), prevNode(prev) {}
};

template<typename T>
FindNodeResult<T> find(LinkedList<T>& list, T value) {
    Node<T>* current = list.firstNode;
    Node<T>* previous = nullptr;

    while (current != nullptr) {
        if (current->value == value) {
            return { current, previous };
        }
        previous = current;
        current = current->nextNode;
    }

    return FindNodeResult<T>(nullptr, nullptr);
}

template<typename T>
void removeAfter(LinkedList<T>& list, Node<T>* node) {
    if (node == nullptr) {
        assert(list.firstNode != nullptr && "list is empty, cannot remove");
        
        Node<T>* nodeToRemove = list.firstNode;
        list.firstNode = list.firstNode->nextNode;

        if (list.firstNode == nullptr) {
            list.lastNode = nullptr;
        }

        delete nodeToRemove;
    } else {
        Node<T>* nodeToRemove = node->nextNode;
        if (nodeToRemove == nullptr) {
            return;
        }

        node->nextNode = nodeToRemove->nextNode;

        if (nodeToRemove == list.lastNode) {
            list.lastNode = node;
        }

        delete nodeToRemove;
    }

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
    insertAfter(list, second, 7);
    insertAfter(list, first, 20);
    insertAfter(list, first, 15);

    std::cout << "list is: " ;
    Node<int>* current = list.firstNode;
    while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->nextNode;
    }
    std::cout << "\n";

    FindNodeResult<int> result = find(list, 20);
    assert(result.foundNode != nullptr && "Cannot find node with this value");
    std::cout << "Found value: " << result.foundNode->value << "\n";
    assert(result.prevNode != nullptr && "prev node is null");
    std::cout << "Previous node to " << result.foundNode->value << " is: " << result.prevNode->value << "\n";

    removeAfter(list, first);

    assertNoCycles(list);

    std::cout << "list is now after removeAfter is called on first node: " ;
    current = list.firstNode;
    while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->nextNode;
    }
    std::cout << "\n";

    return 0;
}

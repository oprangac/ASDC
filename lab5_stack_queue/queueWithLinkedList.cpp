#include <iostream>

struct Node {
    int data;
    Node* next;
};

struct Queue {
    Node* front;
    Node* back;

    Queue() : front(nullptr), back(nullptr) {}

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    // Adds an element to the back of the queue
    void enqueue(int value) {
        Node* newNode = new Node{value, nullptr};
        if (isEmpty()) {
            front = back = newNode;
        } else {
            back->next = newNode;
            back = newNode;
        }
    }

    // Returns the address of the front element without removing it
    int* frontElement() const {
        if (isEmpty()) {
            return nullptr;
        }
        return &(front->data);
    }

    // Removes the front element from the queue
    void dequeue() {
        if (isEmpty()) {
            std::cerr << "Error: Queue is empty. Cannot dequeue." << std::endl;
            return;
        }

        Node* temp = front;
        front = front->next;
        delete temp;

        // If the queue is now empty, reset the back pointer as well
        if (front == nullptr) {
            back = nullptr;
        }
    }
};

int main() {
    Queue queue;

    // Test the queue
    std::cout << "Queue is empty: " << std::boolalpha << queue.isEmpty() << "\n";

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    std::cout << "Queue is empty: " << std::boolalpha << queue.isEmpty() << "\n";
    if (queue.frontElement()) {
        std::cout << "Front element: " << *queue.frontElement() << "\n";
    }

    queue.dequeue();
    if (queue.frontElement()) {
        std::cout << "Front element after dequeue: " << *queue.frontElement() << "\n";
    }

    queue.dequeue();
    queue.dequeue();
    queue.dequeue();

    return 0;
}

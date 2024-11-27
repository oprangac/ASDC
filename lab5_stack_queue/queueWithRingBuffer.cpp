#include <iostream>
#include <stdexcept>

struct Queue {
    int* data;        // Dynamic array to hold the queue elements
    int capacity;     // Total capacity of the queue
    int front;        // Index of the front element
    int back;         // Index of the next position to insert at the back
    int size;         // Current number of elements in the queue

    Queue(int initialCapacity = 4)
        : capacity(initialCapacity), front(0), back(0), size(0) {
        data = new int[capacity];
    }

    ~Queue() {
        delete[] data;
    }

    bool isEmpty() const {
        return size == 0;
    }

    bool isFull() const {
        return size == capacity;
    }

    void enqueue(int value) {
        if (isFull()) {
            resize(capacity * 2);  // Double the capacity if full
        }
        data[back] = value;            // Add the element at the back
        back = (back + 1) % capacity;  // Move the back pointer circularly
        size++;                        // Increment the size
    }

    int* frontElement() const {
        if (isEmpty()) {
            return nullptr;
        }
        return &data[front];
    }

    // Removes the front element from the queue
    void dequeue() {
        if (isEmpty()) {
            std::cerr << "Error: Queue is empty. Cannot dequeue." << std::endl;
            return;
        }
        front = (front + 1) % capacity;  // Move the front pointer circularly
        size--;                          // Decrement the size
    }

    // Resizes the queue to a new capacity
    void resize(int newCapacity) {
        int* newData = new int[newCapacity];
        // Copy elements to the new array in the correct order
        for (int i = 0; i < size; i++) {
            newData[i] = data[(front + i) % capacity];
        }
        delete[] data;
        data = newData;
        front = 0;
        back = size;
        capacity = newCapacity;
    }
};

int main() {
    Queue queue;

    // Test the queue
    std::cout << "Queue is empty: " << std::boolalpha << queue.isEmpty() << "\n";

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.enqueue(40);

    std::cout << "Queue is empty: " << std::boolalpha << queue.isEmpty() << "\n";
    if (queue.frontElement()) {
        std::cout << "Front element: " << *queue.frontElement() << "\n";
    }

    queue.dequeue();
    if (queue.frontElement()) {
        std::cout << "Front element after dequeue: " << *queue.frontElement() << "\n";
    }

    queue.enqueue(50);
    queue.enqueue(60);

    while (!queue.isEmpty()) {
        std::cout << "Dequeuing: " << *queue.frontElement() << "\n";
        queue.dequeue();
    }

    queue.dequeue();

    return 0;
}

#include <iostream>

struct Node {
    int data;
    Node* next;
};

struct Stack {
    Node* top;

    Stack() : top(nullptr) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    void push(int value) {
        Node* newNode = new Node{value, top};
        top = newNode;
    }

    int* getLastElement() const {
        if (isEmpty()) {
            return nullptr;
        }
        return &(top->data);
    }

    void pop() {
        if (isEmpty()) {
            std::cerr << "Error: Stack is empty. Cannot pop." << std::endl;
            return;
        }

        Node* temp = top;
        top = top->next;
        delete temp;          // Free the memory of the removed node
    }
};

int main() {
    Stack stack;

    // Test the stack
    std::cout << "Stack is empty: " << std::boolalpha << stack.isEmpty() << "\n";

    stack.push(10);
    stack.push(20);
    stack.push(30);

    std::cout << "Stack is empty: " << std::boolalpha << stack.isEmpty() << "\n";
    if (stack.getLastElement()) {
        std::cout << "Last element: " << *stack.getLastElement() << "\n";
    }

    stack.pop();
    if (stack.getLastElement()) {
        std::cout << "Last element after pop: " << *stack.getLastElement() << "\n";
    }

    stack.pop();
    stack.pop();
    stack.pop();

    return 0;
}

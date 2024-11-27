#include <iostream>
#include <vector>

struct Stack {
    std::vector<int> data;

    bool isEmpty() const {
        return data.empty();
    }

    void push(int value) {
        data.push_back(value);
    }

    int* getLastElement() {
        if (isEmpty()) {
            return nullptr;
        }
        return &data.back();
    }

    void pop() {
        if (!isEmpty()) {
            data.pop_back();
        } else {
            std::cerr << "Error: Stack is empty. Cannot pop." << std::endl;
        }
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
    std::cout << "Last element: " << *stack.getLastElement() << "\n";

    stack.pop();
    std::cout << "Last element after pop: " << *stack.getLastElement() << "\n";

    stack.pop();
    stack.pop();
    stack.pop();

    return 0;
}

#include <iostream>
#include <vector>
#include <stack>
#include <queue>

struct GraphNode {
    int value;
    std::vector<GraphNode*> neighbors;

    GraphNode(int val) : value(val) {}
};

void addEdge(GraphNode* from, GraphNode* to) {
    from->neighbors.push_back(to);
}

bool isVisited(const std::vector<GraphNode*>& visited, GraphNode* node) {
    for (GraphNode* visitedNode : visited) {
        if (visitedNode == node) { // Compares pointers
            return true;
        }
    }
    return false;
}

int sumOfNeighbors(GraphNode* node) {
    int sum = 0;
    for (GraphNode* neighbor : node->neighbors) {
        sum += neighbor->value;
    }
    return sum;
}

void DFS(GraphNode* start) {
    std::vector<GraphNode*> nodesToVisit;
    std::vector<GraphNode*> visited;

    nodesToVisit.push_back(start);

    std::cout << "DFS Traversal: ";
    while (!nodesToVisit.empty()) {
        GraphNode* current = nodesToVisit.back();
        nodesToVisit.pop_back();

        if (isVisited(visited, current)) {
            continue;
        }

        visited.push_back(current);
        std::cout << current->value << " ";

        for (auto it = current->neighbors.rbegin(); it != current->neighbors.rend(); ++it) {
            nodesToVisit.push_back(*it);
        }
    }
    std::cout << std::endl;
}

void BFS(GraphNode* start) {
    std::queue<GraphNode*> queue;
    std::vector<GraphNode*> visited;

    queue.push(start);

    std::cout << "BFS Traversal: ";
    while (!queue.empty()) {
        GraphNode* current = queue.front();
        queue.pop();

        if (isVisited(visited, current)) {
            continue;
        }

        visited.push_back(current);
        std::cout << current->value << " ";

        for (GraphNode* neighbor : current->neighbors) {
            queue.push(neighbor);
        }
    }
    std::cout << std::endl;
}

int main() {
    GraphNode* node1 = new GraphNode(1);
    GraphNode* node2 = new GraphNode(2);
    GraphNode* node3 = new GraphNode(3);
    GraphNode* node4 = new GraphNode(4);

    addEdge(node1, node2);
    addEdge(node2, node3);
    addEdge(node3, node4);
    addEdge(node4, node1);
    addEdge(node1, node3);
    addEdge(node1, node4);

    std::cout << "Sum of neighbors for node 1: " << sumOfNeighbors(node1) << std::endl;
    std::cout << "Sum of neighbors for node 2: " << sumOfNeighbors(node2) << std::endl;
    std::cout << "Sum of neighbors for node 3: " << sumOfNeighbors(node3) << std::endl;
    std::cout << "Sum of neighbors for node 4: " << sumOfNeighbors(node4) << std::endl;

    DFS(node1);
    BFS(node1);

    delete node1;
    delete node2;
    delete node3;
    delete node4;

    return 0;
}

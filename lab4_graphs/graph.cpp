#include <iostream>
#include <vector>
#include <stack>
#include <queue>

struct GraphNode {
    int value;
    std::vector<GraphNode*> neighbors;   // List of neighbors (using std::vector)

    GraphNode(int val) : value(val) {}
};

// Function to add a directed edge between two nodes
void addEdge(GraphNode* from, GraphNode* to) {
    from->neighbors.push_back(to); // Add 'to' as a neighbor of 'from'
}

bool isVisited(const std::vector<GraphNode*>& visited, GraphNode* node) {
    for (GraphNode* visitedNode : visited) {
        if (visitedNode == node) { // Compare pointers to check if the node is in the list
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

// Depth First Search (DFS)
void DFS(GraphNode* start) {
    std::vector<GraphNode*> nodesToVisit;
    std::vector<GraphNode*> visited;

    nodesToVisit.push_back(start); // Add the start node

    std::cout << "Custom DFS Traversal: ";
    while (!nodesToVisit.empty()) {
        GraphNode* current = nodesToVisit.back(); // Get the last node
        nodesToVisit.pop_back();                  // Remove the last node

        if (isVisited(visited, current)) {
            continue; // Skip already visited nodes
        }

        visited.push_back(current);
        std::cout << current->value << " ";

        for (auto it = current->neighbors.rbegin(); it != current->neighbors.rend(); ++it) {
            nodesToVisit.push_back(*it);
        }
    }
    std::cout << std::endl;
}

// Breadth First Search (BFS)
void BFS(GraphNode* start) {
    std::vector<GraphNode*> nodesToExplore;
    std::vector<GraphNode*> visited;

    nodesToExplore.push_back(start); // Add the start node

    std::cout << "Custom BFS Traversal: ";
    while (!nodesToExplore.empty()) {
        GraphNode* current = nodesToExplore.front(); // Get the first node
        nodesToExplore.erase(nodesToExplore.begin()); // Remove the first node

        if (isVisited(visited, current)) {
            continue; // Skip already visited nodes
        }

        visited.push_back(current);
        std::cout << current->value << " ";

        for (GraphNode* neighbor : current->neighbors) {
            nodesToExplore.push_back(neighbor);
        }
    }
    std::cout << std::endl;
}



int main() {
    // Create nodes
    GraphNode* node1 = new GraphNode(1);
    GraphNode* node2 = new GraphNode(2);
    GraphNode* node3 = new GraphNode(3);
    GraphNode* node4 = new GraphNode(4);

    // Build the directed graph
    addEdge(node1, node2); // 1 → 2
    addEdge(node2, node3); // 2 → 3
    addEdge(node3, node4); // 3 → 4
    addEdge(node4, node1); // 4 → 1
    addEdge(node1, node3); // 1 → 3
    addEdge(node1, node4); // 1 → 4

    // Perform operations
    std::cout << "Sum of neighbors for node 1: " << sumOfNeighbors(node1) << std::endl;
    std::cout << "Sum of neighbors for node 2: " << sumOfNeighbors(node2) << std::endl;
    std::cout << "Sum of neighbors for node 3: " << sumOfNeighbors(node3) << std::endl;
    std::cout << "Sum of neighbors for node 4: " << sumOfNeighbors(node4) << std::endl;

    // Traversals
    DFS(node1);
    BFS(node1);

    // Clean up memory
    delete node1;
    delete node2;
    delete node3;
    delete node4;

    return 0;
}

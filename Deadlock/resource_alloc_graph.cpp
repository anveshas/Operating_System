#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// Class to represent a Resource Allocation Graph
class ResourceAllocationGraph {
public:
    unordered_map<string, vector<string> > graph;  // Adjacency list for RAG

    // Add an edge from process to resource (request edge)
    void addRequestEdge(const string& process, const string& resource) {
        graph[process].push_back(resource);
    }

    // Add an edge from resource to process (assignment edge)
    void addAssignmentEdge(const string& resource, const string& process) {
        graph[resource].push_back(process);
    }

    // Display the graph
    void displayGraph() {
        cout << "Resource Allocation Graph:" << endl;
        for (auto& node : graph) {
            cout << node.first << " -> ";
            for (const auto& neighbor : node.second) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // Cycle detection using Depth-First Search (DFS)
    bool detectCycleUtil(const string& node, unordered_set<string>& visited, unordered_set<string>& recStack) {
        visited.insert(node);
        recStack.insert(node);

        for (const auto& neighbor : graph[node]) {
            if (recStack.find(neighbor) != recStack.end()) {
                return true;  // Cycle detected
            }
            if (visited.find(neighbor) == visited.end() && detectCycleUtil(neighbor, visited, recStack)) {
                return true;
            }
        }

        recStack.erase(node);
        return false;
    }

    // Detect if there is a cycle (potential deadlock)
    bool detectCycle() {
        unordered_set<string> visited;
        unordered_set<string> recStack;

        for (const auto& node : graph) {
            if (visited.find(node.first) == visited.end()) {
                if (detectCycleUtil(node.first, visited, recStack)) {
                    return true;  // Cycle (deadlock) found
                }
            }
        }
        return false;
    }
};

int main() {
    ResourceAllocationGraph rag;

    // Example 1: Constructing the RAG
    rag.addRequestEdge("P1", "R1");  // Process P1 requests Resource R1
    rag.addAssignmentEdge("R1", "P2");  // Resource R1 assigned to Process P2
    rag.addRequestEdge("P2", "R2");  // Process P2 requests Resource R2
    rag.addAssignmentEdge("R2", "P3");  // Resource R2 assigned to Process P3
    rag.addRequestEdge("P3", "R3");  // Process P3 requests Resource R3
    rag.addAssignmentEdge("R3", "P1");  // Resource R3 assigned to Process P1 (cycle)

    // Display the Resource Allocation Graph
    rag.displayGraph();

    // Detect cycle (deadlock detection)
    if (rag.detectCycle()) {
        cout << "Deadlock detected!" << endl;
    } else {
        cout << "No deadlock detected." << endl;
    }

    return 0;
}

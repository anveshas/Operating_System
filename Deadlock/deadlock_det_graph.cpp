#include <iostream>
#include <vector>

bool is_deadlock(const std::vector<std::vector<int>>& graph) {
    int n = graph.size();
    std::vector<bool> visited(n, false);
    std::vector<bool> recStack(n, false);

    auto dfs = [&](int node, auto&& dfs_ref) -> bool {
        visited[node] = true;
        recStack[node] = true;

        for (int neighbor : graph[node]) {
            if (!visited[neighbor] && dfs_ref(neighbor, dfs_ref)) {
                return true;
            } else if (recStack[neighbor]) {
                return true; // Cycle detected
            }
        }

        recStack[node] = false;
        return false;
    };

    for (int i = 0; i < n; ++i) {
        if (!visited[i] && dfs(i, dfs)) {
            return true;
        }
    }

    return false;
}

int main() {
    std::vector<std::vector<int>> wait_for_graph = {
        {1},   // Process 0 waits for Process 1
        {2},   // Process 1 waits for Process 2
        {0}    // Process 2 waits for Process 0 -> Deadlock!
    };

    if (is_deadlock(wait_for_graph)) {
        std::cout << "Deadlock detected!" << std::endl;
    } else {
        std::cout << "No deadlock." << std::endl;
    }

    return 0;
}

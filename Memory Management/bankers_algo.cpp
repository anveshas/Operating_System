#include <iostream>
#include <vector>

bool isSafe(const std::vector<int>& available, const std::vector<std::vector<int>>& max,
            const std::vector<std::vector<int>>& allocation, const std::vector<std::vector<int>>& need) {
    std::vector<int> work = available;
    std::vector<bool> finish(max.size(), false);
    std::vector<int> safe_sequence;

    for (int k = 0; k < max.size(); k++) {
        bool found = false;
        for (int i = 0; i < max.size(); i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < available.size(); j++) {
                    if (need[i][j] > work[j]) break;
                }
                if (j == available.size()) {
                    for (int m = 0; m < available.size(); m++) {
                        work[m] += allocation[i][m];
                    }
                    safe_sequence.push_back(i);
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            std::cout << "System is not in a safe state!" << std::endl;
            return false;
        }
    }
    std::cout << "System is in a safe state. Safe sequence: ";
    for (int i : safe_sequence) std::cout << i << " ";
    std::cout << std::endl;
    return true;
}

int main() {
    std::vector<int> available = {3, 3, 2};
    std::vector<std::vector<int>> max = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
    std::vector<std::vector<int>> allocation = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
    std::vector<std::vector<int>> need = {{7, 4, 3}, {1, 2, 2}, {6, 0, 0}, {0, 1, 1}, {4, 3, 1}};

    isSafe(available, max, allocation, need);
    return 0;
}

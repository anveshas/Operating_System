#include <iostream>
#include <vector>

using namespace std;

void pagingSimulation(int processes[], int numProcesses, int pageSize) {
    cout << "Paging Simulation: \n";
    cout << "Page Size: " << pageSize << " units.\n";
    
    for (int i = 0; i < numProcesses; i++) {
        int processSize = processes[i];
        int pagesNeeded = (processSize + pageSize - 1) / pageSize;  // Rounds up

        cout << "Process " << i + 1 << " (Size: " << processSize << " units) "
             << "needs " << pagesNeeded << " pages.\n";

        cout << "Pages allocated: ";
        for (int j = 0; j < pagesNeeded; j++) {
            cout << "Page " << j + 1 << " ";
        }
        cout << "\n";
    }
}

int main() {
    int pageSize = 4;  // Assume each page is 4 units of memory

    // Array to store process sizes
    int processes[] = {10, 8, 15, 6};
    int numProcesses = sizeof(processes) / sizeof(processes[0]);

    pagingSimulation(processes, numProcesses, pageSize);

    return 0;
}

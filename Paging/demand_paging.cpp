#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

// Function to simulate demand paging using FIFO page replacement
void DemandPagingFIFO(int pages[], int n, int capacity) {
    unordered_set<int> memory;       // Stores the pages in memory
    queue<int> pageQueue;            // Queue to implement FIFO page replacement
    int pageFaults = 0;              // Count of page faults

    // Loop through all the page requests
    for (int i = 0; i < n; i++) {
        int currentPage = pages[i];

        // If the page is not in memory (Page Fault)
        if (memory.find(currentPage) == memory.end()) {
            // If memory is full, replace the oldest page (FIFO)
            if (memory.size() == capacity) {
                int pageToRemove = pageQueue.front();  // The oldest page in memory
                pageQueue.pop();                      // Remove it from the queue
                memory.erase(pageToRemove);           // Remove it from memory
            }

            // Add the new page into memory and the queue
            memory.insert(currentPage);
            pageQueue.push(currentPage);

            // Increment the page fault counter
            pageFaults++;
        }

        // Output current memory status
        cout << "After accessing page " << currentPage << ": ";
        for (const int &p : memory) {
            cout << p << " ";
        }
        cout << endl;
    }

    cout << "Total Page Faults: " << pageFaults << endl;
}

int main() {
    // Example page reference string
    int pages[] = {1, 3, 0, 3, 5, 6, 3, 0, 1, 2};
    int n = sizeof(pages) / sizeof(pages[0]);

    // Define the memory capacity (number of frames)
    int capacity = 3;

    // Run the demand paging simulation
    DemandPagingFIFO(pages, n, capacity);

    return 0;
}

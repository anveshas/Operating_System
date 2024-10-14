#include <iostream>
#include <unordered_map>
#include <queue>

using namespace std;

class TLB {
private:
    unordered_map<int, int> tlbMap;  // Stores virtual-to-physical address mappings
    queue<int> tlbQueue;             // Queue to maintain FIFO order of entries
    int capacity;                    // TLB capacity (number of entries)
    int hits;                        // Count of TLB hits
    int misses;                      // Count of TLB misses

public:
    // Constructor to initialize TLB with a given capacity
    TLB(int cap) : capacity(cap), hits(0), misses(0) {}

    // Method to search for a page in the TLB (TLB lookup)
    void accessTLB(int virtualAddress, int physicalAddress) {
        // TLB hit: the virtual address is already in TLB
        if (tlbMap.find(virtualAddress) != tlbMap.end()) {
            hits++;
            cout << "TLB Hit: Virtual Address " << virtualAddress << " -> Physical Address " << tlbMap[virtualAddress] << endl;
        }
        // TLB miss: the virtual address is not in the TLB
        else {
            misses++;
            cout << "TLB Miss: Virtual Address " << virtualAddress << " not found in TLB." << endl;

            // If TLB is full, remove the oldest entry (FIFO)
            if (tlbQueue.size() == capacity) {
                int oldestVirtualAddr = tlbQueue.front();
                tlbQueue.pop();
                tlbMap.erase(oldestVirtualAddr);  // Remove the oldest entry from the TLB
            }

            // Add the new virtual-to-physical address mapping to TLB
            tlbQueue.push(virtualAddress);
            tlbMap[virtualAddress] = physicalAddress;
            cout << "Added: Virtual Address " << virtualAddress << " -> Physical Address " << physicalAddress << " to TLB." << endl;
        }
    }

    // Method to display TLB hits and misses statistics
    void displayStats() const {
        cout << "TLB Hits: " << hits << endl;
        cout << "TLB Misses: " << misses << endl;
    }
};

int main() {
    // Simulated page requests with virtual addresses and corresponding physical addresses
    int pages[][2] = {
        {1, 101}, {2, 102}, {3, 103}, {4, 104}, {1, 101},
        {5, 105}, {6, 106}, {2, 102}, {7, 107}, {1, 101},
    };
    int n = sizeof(pages) / sizeof(pages[0]);

    // TLB capacity (number of entries)
    int tlbCapacity = 4;

    // Create a TLB object with the specified capacity
    TLB tlb(tlbCapacity);

    // Simulate accessing the pages through the TLB
    for (int i = 0; i < n; i++) {
        int virtualAddress = pages[i][0];
        int physicalAddress = pages[i][1];
        tlb.accessTLB(virtualAddress, physicalAddress);
    }

    // Display the final statistics of TLB hits and misses
    tlb.displayStats();

    return 0;
}

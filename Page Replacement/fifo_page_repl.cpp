#include <iostream>
#include <queue>
#include <unordered_set>

// {1, 3, 0, 3, 5, 6, 3}
// Capacity of memory frames is 3
// Total Page Faults (FIFO): 5

void fifoPageReplacement(int pages[], int n, int capacity) {
    std::unordered_set<int> page_set;
    std::queue<int> page_queue;
    int page_faults = 0;

    for (int i = 0; i < n; i++) {
        if (page_set.size() < capacity) {
            if (page_set.find(pages[i]) == page_set.end()) {
                page_set.insert(pages[i]);
                page_queue.push(pages[i]);
                page_faults++;
            }
        } else {
            if (page_set.find(pages[i]) == page_set.end()) {
                int old_page = page_queue.front();
                page_queue.pop();
                page_set.erase(old_page);

                page_set.insert(pages[i]);
                page_queue.push(pages[i]);
                page_faults++;
            }
        }
    }

    std::cout << "Total page faults = " << page_faults << std::endl;
}

int main() {
    int pages[] = {1, 3, 0, 3, 5, 6};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    fifoPageReplacement(pages, n, capacity);
    return 0;
}

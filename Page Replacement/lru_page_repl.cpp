#include <iostream>
#include <unordered_set>
#include <unordered_map>

// {1, 3, 0, 3, 5, 6, 3}
// Capacity of memory frames is 3
// Total Page Faults (LRU): 5

void lruPageReplacement(int pages[], int n, int capacity) {
    std::unordered_set<int> page_set;
    std::unordered_map<int, int> page_index;
    int page_faults = 0;

    for (int i = 0; i < n; i++) {
        if (page_set.size() < capacity) {
            if (page_set.find(pages[i]) == page_set.end()) {
                page_set.insert(pages[i]);
                page_faults++;
            }
            page_index[pages[i]] = i;
        } else {
            if (page_set.find(pages[i]) == page_set.end()) {
                int lru = INT_MAX, val;
                for (auto it : page_set) {
                    if (page_index[it] < lru) {
                        lru = page_index[it];
                        val = it;
                    }
                }

                page_set.erase(val);
                page_set.insert(pages[i]);
                page_faults++;
            }
            page_index[pages[i]] = i;
        }
    }

    std::cout << "Total page faults = " << page_faults << std::endl;
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 4;

    lruPageReplacement(pages, n, capacity);
    return 0;
}

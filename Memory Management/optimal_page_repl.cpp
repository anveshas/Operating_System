#include <iostream>
#include <vector>
#include <algorithm>

int predict(const std::vector<int>& pages, const std::vector<int>& frames, int index) {
    int res = -1, farthest = index;
    for (int i = 0; i < frames.size(); i++) {
        int j;
        for (j = index; j < pages.size(); j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == pages.size()) {
            return i;
        }
    }
    return (res == -1) ? 0 : res;
}

void optimalPageReplacement(const std::vector<int>& pages, int num_frames) {
    std::vector<int> frames;
    int hit = 0, fault = 0;

    for (int i = 0; i < pages.size(); i++) {
        if (std::find(frames.begin(), frames.end(), pages[i]) != frames.end()) {
            hit++;
            continue;
        }

        if (frames.size() < num_frames) {
            frames.push_back(pages[i]);
        } else {
            int j = predict(pages, frames, i + 1);
            frames[j] = pages[i];
        }

        fault++;
    }

    std::cout << "Total Hits: " << hit << "\n";
    std::cout << "Total Faults: " << fault << "\n";
}

int main() {
    std::vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int num_frames = 3;

    optimalPageReplacement(pages, num_frames);
    return 0;
}

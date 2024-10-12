#include <iostream>
#include <vector>
#include <algorithm>

void scanDiskScheduling(std::vector<int>& requests, int head, int direction, int disk_size) {
    std::vector<int> left, right;
    int seek_count = 0, distance;

    if (direction == 0) {  // Moving left
        left.push_back(0);
    } else {  // Moving right
        right.push_back(disk_size - 1);
    }

    for (int i = 0; i < requests.size(); i++) {
        if (requests[i] < head) {
            left.push_back(requests[i]);
        } else {
            right.push_back(requests[i]);
        }
    }

    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    std::vector<int> seek_sequence;

    if (direction == 0) {
        for (int i = left.size() - 1; i >= 0; i--) {
            seek_sequence.push_back(left[i]);
            distance = abs(head - left[i]);
            seek_count += distance;
            head = left[i];
        }
        for (int i = 0; i < right.size(); i++) {
            seek_sequence.push_back(right[i]);
            distance = abs(head - right[i]);
            seek_count += distance;
            head = right[i];
        }
    } else {
        for (int i = 0; i < right.size(); i++) {
            seek_sequence.push_back(right[i]);
            distance = abs(head - right[i]);
            seek_count += distance;
            head = right[i];
        }
        for (int i = left.size() - 1; i >= 0; i--) {
            seek_sequence.push_back(left[i]);
            distance = abs(head - left[i]);
            seek_count += distance;
            head = left[i];
        }
    }

    std::cout << "Total seek operations: " << seek_count << std::endl;
    std::cout << "Seek sequence: ";
    for (int i : seek_sequence) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> requests = {176, 79, 34, 60, 92, 11, 41, 114};
    int head = 50;
    int direction = 1;  // 0 for left, 1 for right
    int disk_size = 200;

    scanDiskScheduling(requests, head, direction, disk_size);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Structure to represent a memory segment
struct Segment {
    string name;     // Segment name (e.g., Code, Data, Stack)
    int base;        // Base address
    int limit;       // Limit address (size of segment)

    Segment(string n, int b, int l) : name(n), base(b), limit(l) {}
};

// Class to represent a memory model using segmentation
class Segmentation {
private:
    vector<Segment> segments;  // List of segments in memory

public:
    // Method to add a segment
    void addSegment(string name, int base, int limit) {
        Segment segment(name, base, limit);
        segments.push_back(segment);
    }

    // Method to display the segments
    void displaySegments() {
        cout << "Memory Segments: " << endl;
        cout << "---------------------------------" << endl;
        cout << "Segment\tBase Address\tLimit" << endl;
        cout << "---------------------------------" << endl;
        for (auto& segment : segments) {
            cout << segment.name << "\t" << segment.base << "\t\t" << segment.limit << endl;
        }
    }

    // Method to simulate accessing a segment
    void accessMemory(string segmentName, int offset) {
        bool found = false;
        for (auto& segment : segments) {
            if (segment.name == segmentName) {
                found = true;
                if (offset < segment.limit) {
                    cout << "Accessing " << segmentName << " segment at address " << segment.base + offset << endl;
                } else {
                    cout << "Error: Offset exceeds the limit of the " << segmentName << " segment." << endl;
                }
                break;
            }
        }
        if (!found) {
            cout << "Error: Segment " << segmentName << " not found." << endl;
        }
    }
};

int main() {
    Segmentation memory;

    // Adding segments with their base and limit addresses
    memory.addSegment("Code", 0, 500);   // Base address 0, limit (size) 500
    memory.addSegment("Data", 500, 300); // Base address 500, limit (size) 300
    memory.addSegment("Stack", 800, 200); // Base address 800, limit (size) 200

    // Display the segments
    memory.displaySegments();

    // Accessing memory within different segments
    memory.accessMemory("Code", 100);  // Valid access
    memory.accessMemory("Data", 250);  // Valid access
    memory.accessMemory("Stack", 50);  // Valid access

    // Trying to access memory outside the limit of a segment
    memory.accessMemory("Code", 600);  // Invalid access - exceeds limit

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>

struct Process {
    int pid;
    int burst_time;
    int remaining_time;
};

void findWaitingTime(std::vector<Process>& processes, int quantum, std::vector<int>& waiting_time) {
    int t = 0; // Current time
    while (true) {
        bool done = true;
        for (int i = 0; i < processes.size(); i++) {
            if (processes[i].remaining_time > 0) {
                done = false;
                if (processes[i].remaining_time > quantum) {
                    t += quantum;
                    processes[i].remaining_time -= quantum;
                } else {
                    t += processes[i].remaining_time;
                    waiting_time[i] = t - processes[i].burst_time;
                    processes[i].remaining_time = 0;
                }
            }
        }
        if (done) break;
    }
}

void findTurnAroundTime(const std::vector<Process>& processes, const std::vector<int>& waiting_time, std::vector<int>& turnaround_time) {
    for (int i = 0; i < processes.size(); i++) {
        turnaround_time[i] = processes[i].burst_time + waiting_time[i];
    }
}

void findAvgTime(std::vector<Process>& processes, int quantum) {
    std::vector<int> waiting_time(processes.size());
    std::vector<int> turnaround_time(processes.size());

    for (int i = 0; i < processes.size(); i++) {
        processes[i].remaining_time = processes[i].burst_time;
    }

    findWaitingTime(processes, quantum, waiting_time);
    findTurnAroundTime(processes, waiting_time, turnaround_time);

    std::cout << "Processes  Burst time  Waiting time  Turnaround time\n";

    for (int i = 0; i < processes.size(); i++) {
        std::cout << " " << processes[i].pid << "\t\t" << processes[i].burst_time << "\t\t"
                  << waiting_time[i] << "\t\t" << turnaround_time[i] << std::endl;
    }
}

int main() {
    std::vector<Process> processes = {{1, 10}, {2, 5}, {3, 8}};
    int quantum = 2;
    findAvgTime(processes, quantum);
    return 0;
}

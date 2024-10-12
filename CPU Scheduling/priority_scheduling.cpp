#include <iostream>
#include <vector>
#include <algorithm>

struct Process {
    int pid;        // Process ID
    int burst_time;
    int priority;
};

bool comparePriority(Process a, Process b) {
    return a.priority > b.priority;
}

void findWaitingTime(const std::vector<Process>& processes, std::vector<int>& waiting_time) {
    waiting_time[0] = 0;
    for (int i = 1; i < processes.size(); i++) {
        waiting_time[i] = processes[i - 1].burst_time + waiting_time[i - 1];
    }
}

void findTurnAroundTime(const std::vector<Process>& processes, const std::vector<int>& waiting_time, std::vector<int>& turnaround_time) {
    for (int i = 0; i < processes.size(); i++) {
        turnaround_time[i] = processes[i].burst_time + waiting_time[i];
    }
}

void findAvgTime(std::vector<Process>& processes) {
    std::vector<int> waiting_time(processes.size());
    std::vector<int> turnaround_time(processes.size());

    std::sort(processes.begin(), processes.end(), comparePriority);

    findWaitingTime(processes, waiting_time);
    findTurnAroundTime(processes, waiting_time, turnaround_time);

    std::cout << "Processes  Burst time  Priority  Waiting time  Turnaround time\n";
    for (int i = 0; i < processes.size(); i++) {
        std::cout << " " << processes[i].pid << "\t\t" << processes[i].burst_time << "\t\t"
                  << processes[i].priority << "\t\t" << waiting_time[i] << "\t\t"
                  << turnaround_time[i] << std::endl;
    }
}

int main() {
    std::vector<Process> processes = {{1, 10, 1}, {2, 5, 3}, {3, 8, 2}};
    findAvgTime(processes);
    return 0;
}

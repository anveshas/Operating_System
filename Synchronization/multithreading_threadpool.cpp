#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

std::queue<std::function<void()>> task_queue;
std::mutex mtx;
std::condition_variable cv;
bool stop = false;

void workerThread() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [] { return !task_queue.empty() || stop; });
            if (stop && task_queue.empty()) return;
            task = task_queue.front();
            task_queue.pop();
        }
        task();
    }
}

void submitTask(std::function<void()> task) {
    {
        std::lock_guard<std::mutex> lock(mtx);
        task_queue.push(task);
    }
    cv.notify_one();
}

int main() {
    int num_threads = 4;
    std::vector<std::thread> thread_pool;

    for (int i = 0; i < num_threads; i++) {
        thread_pool.push_back(std::thread(workerThread));
    }

    for (int i = 0; i < 10; i++) {
        submitTask([i] { std::cout << "Task " << i << " is being processed by thread " << std::this_thread::get_id() << std::endl; });
    }

    {
        std::lock_guard<std::mutex> lock(mtx);
        stop = true;
    }
    cv.notify_all();

    for (auto& thread : thread_pool) {
        thread.join();
    }

    return 0;
}

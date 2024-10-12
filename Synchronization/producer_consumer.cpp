#include <iostream>
#include <queue>
#include <pthread.h>
#include <unistd.h>

std::queue<int> buffer;
const unsigned int MAX_BUFFER_SIZE = 10;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buffer_not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_not_empty = PTHREAD_COND_INITIALIZER;

void* producer(void* arg) {
    int item = 0;
    while (true) {
        pthread_mutex_lock(&mutex);

        while (buffer.size() == MAX_BUFFER_SIZE) {
            pthread_cond_wait(&buffer_not_full, &mutex);
        }

        buffer.push(item);
        std::cout << "Produced: " << item++ << std::endl;

        pthread_cond_signal(&buffer_not_empty);
        pthread_mutex_unlock(&mutex);

        sleep(1); // Simulate time for production
    }
}

void* consumer(void* arg) {
    while (true) {
        pthread_mutex_lock(&mutex);

        while (buffer.empty()) {
            pthread_cond_wait(&buffer_not_empty, &mutex);
        }

        int item = buffer.front();
        buffer.pop();
        std::cout << "Consumed: " << item << std::endl;

        pthread_cond_signal(&buffer_not_full);
        pthread_mutex_unlock(&mutex);

        sleep(2); // Simulate time for consumption
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;

    pthread_create(&producer_thread, nullptr, producer, nullptr);
    pthread_create(&consumer_thread, nullptr, consumer, nullptr);

    pthread_join(producer_thread, nullptr);
    pthread_join(consumer_thread, nullptr);

    return 0;
}

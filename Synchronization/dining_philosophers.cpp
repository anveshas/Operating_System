#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5  // Number of philosophers

sem_t chopstick[N];
pthread_t philosopher[N];

void* dine(void* num) {
    int id = *(int*)num;

    std::cout << "Philosopher " << id << " is thinking.\n";
    sleep(1);

    // Pick up left chopstick
    sem_wait(&chopstick[id]);
    std::cout << "Philosopher " << id << " picked up left chopstick.\n";
    
    // Pick up right chopstick
    sem_wait(&chopstick[(id + 1) % N]);
    std::cout << "Philosopher " << id << " picked up right chopstick.\n";

    std::cout << "Philosopher " << id << " is eating.\n";
    sleep(1);

    // Put down right chopstick
    sem_post(&chopstick[(id + 1) % N]);
    std::cout << "Philosopher " << id << " put down right chopstick.\n";
    
    // Put down left chopstick
    sem_post(&chopstick[id]);
    std::cout << "Philosopher " << id << " put down left chopstick.\n";

    std::cout << "Philosopher " << id << " finished eating.\n";
    
    return nullptr;
}

int main() {
    int ids[N];
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        sem_init(&chopstick[i], 0, 1);
    }

    for (int i = 0; i < N; i++) {
        pthread_create(&philosopher[i], nullptr, dine, &ids[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(philosopher[i], nullptr);
    }

    for (int i = 0; i < N; i++) {
        sem_destroy(&chopstick[i]);
    }

    return 0;
}

#include <iostream>
#include <semaphore.h>
#include <pthread.h>

sem_t semaphore;

void* critical_section(void* arg) {
    sem_wait(&semaphore); // Entering the critical section
    std::cout << "Thread in critical section." << std::endl;
    sem_post(&semaphore); // Exiting the critical section
    return nullptr;
}

int main() {
    pthread_t thread1, thread2;
    
    sem_init(&semaphore, 0, 1); // Initialize the semaphore with value 1

    pthread_create(&thread1, nullptr, critical_section, nullptr);
    pthread_create(&thread2, nullptr, critical_section, nullptr);

    pthread_join(thread1, nullptr);
    pthread_join(thread2, nullptr);

    sem_destroy(&semaphore); // Clean up
    return 0;
}

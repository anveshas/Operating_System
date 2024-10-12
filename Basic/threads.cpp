#include <iostream>
#include <pthread.h>

void* print_message(void* arg) {
    std::cout << "Thread says: Hello, World!" << std::endl;
    return nullptr;
}

int main() {
    pthread_t thread;
    int result = pthread_create(&thread, nullptr, print_message, nullptr);

    if (result != 0) {
        std::cerr << "Error creating thread!" << std::endl;
        return 1;
    }

    pthread_join(thread, nullptr);
    return 0;
}

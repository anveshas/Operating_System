#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>

int main() {
    int pipefd[2];  // pipefd[0] is for reading, pipefd[1] is for writing
    pid_t pid;
    char write_msg[] = "Hello from parent!";
    char read_msg[50];

    // Create the pipe
    if (pipe(pipefd) == -1) {
        std::cerr << "Pipe failed!" << std::endl;
        return 1;
    }

    // Create a child process
    pid = fork();

    if (pid < 0) {
        std::cerr << "Fork failed!" << std::endl;
        return 1;
    }

    if (pid > 0) {
        // Parent process
        close(pipefd[0]);  // Close the reading end of the pipe

        // Write to the pipe
        std::cout << "Parent writing to pipe: " << write_msg << std::endl;
        write(pipefd[1], write_msg, strlen(write_msg) + 1);

        close(pipefd[1]);  // Close the writing end after writing
        wait(NULL);        // Wait for child to finish
    } else {
        // Child process
        close(pipefd[1]);  // Close the writing end of the pipe

        // Read from the pipe
        read(pipefd[0], read_msg, sizeof(read_msg));
        std::cout << "Child read from pipe: " << read_msg << std::endl;

        close(pipefd[0]);  // Close the reading end after reading
    }

    return 0;
}

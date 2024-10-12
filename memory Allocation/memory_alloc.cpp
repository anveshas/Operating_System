#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char* filepath = "example.txt";
    int fd = open(filepath, O_RDWR | O_CREAT, 0600);

    if (fd == -1) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    // Set file size to 128 bytes
    ftruncate(fd, 128);

    // Memory map the file
    char* mapped = (char*) mmap(0, 128, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped == MAP_FAILED) {
        std::cerr << "Error mapping file" << std::endl;
        close(fd);
        return 1;
    }

    // Write to memory-mapped file
    sprintf(mapped, "Hello from mmap!");

    std::cout << "Written: " << mapped << std::endl;

    // Clean up
    munmap(mapped, 128);
    close(fd);

    return 0;
}

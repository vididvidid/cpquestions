#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <sys/ioctl.h>
#include <linux/userfaultfd.h>
#include <poll.h>
#include <fcntl.h>

#define PAGE_SIZE 4096

// This is the background thread that listens for page faults
void* fault_handler_thread(void* arg) {
    long uffd = (long)arg;
    struct uffd_msg msg;
    struct uffdio_copy uffdio_copy;
    char page_buffer[PAGE_SIZE];

    printf("[Listener] Thread started, waiting for page faults...\n");

    // Wait for a message from the userfaultfd file descriptor
    struct pollfd pollfd;
    pollfd.fd = uffd;
    pollfd.events = POLLIN;
    poll(&pollfd, 1, -1);

    // Read the message from the kernel
    read(uffd, &msg, sizeof(msg));

    if (msg.event != UFFD_EVENT_PAGEFAULT) {
        printf("[Listener] Unexpected event!\n");
        return NULL;
    }

    printf("[Listener] CAUGHT A PAGE FAULT at address: %llx\n", msg.arg.pagefault.address);

    // Create the data we want to secretly inject into that memory
    memset(page_buffer, 0, PAGE_SIZE);
    sprintf(page_buffer, "Hello from the userfaultfd listener thread!");

    // Tell the kernel to copy our data into the faulting address and wake up the frozen thread
    uffdio_copy.src = (unsigned long)page_buffer;
    uffdio_copy.dst = (unsigned long)msg.arg.pagefault.address & ~(PAGE_SIZE - 1); // Align to page boundary
    uffdio_copy.len = PAGE_SIZE;
    uffdio_copy.mode = 0; // Wake up the thread immediately
    uffdio_copy.copy = 0;

    printf("[Listener] Injecting data and waking up the main thread...\n");
    if (ioctl(uffd, UFFDIO_COPY, &uffdio_copy) == -1) {
        perror("ioctl(UFFDIO_COPY) failed");
        exit(1);
    }

    return NULL;
}

int main() {
    long uffd;
    char *addr;
    pthread_t thr;
    struct uffdio_api uffdio_api;
    struct uffdio_register uffdio_register;

    // 1. Allocate a page of memory (anonymous, not backed by a file)
    addr = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (addr == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }
    printf("[Main] Allocated 1 page of memory at address: %p\n", addr);

    // 2. Initialize the userfaultfd system call
    uffd = syscall(SYS_userfaultfd, O_CLOEXEC | O_NONBLOCK);
    if (uffd == -1) {
        perror("syscall(SYS_userfaultfd) failed. (Try running with sudo!)");
        exit(1);
    }

    // 3. Enable the userfaultfd API
    uffdio_api.api = UFFD_API;
    uffdio_api.features = 0;
    if (ioctl(uffd, UFFDIO_API, &uffdio_api) == -1) {
        perror("ioctl(UFFDIO_API) failed");
        exit(1);
    }

    // 4. Register our specific memory page with userfaultfd
    uffdio_register.range.start = (unsigned long)addr;
    uffdio_register.range.len = PAGE_SIZE;
    uffdio_register.mode = UFFDIO_REGISTER_MODE_MISSING; // Catch missing pages
    if (ioctl(uffd, UFFDIO_REGISTER, &uffdio_register) == -1) {
        perror("ioctl(UFFDIO_REGISTER) failed");
        exit(1);
    }
    printf("[Main] Successfully registered memory with userfaultfd.\n");

    // 5. Spin up the background listener thread
    pthread_create(&thr, NULL, fault_handler_thread, (void*)uffd);

    // Give the thread a tiny fraction of a second to start up
    usleep(100000); 

    // 6. THE TRAP: Try to read from the memory. 
    // This will instantly freeze the main thread because the memory hasn't been populated yet!
    printf("[Main] Attempting to read from memory...\n");
    
    // --> THREAD FREEZES HERE <--
    printf("[Main] Read successful! The memory says: '%s'\n", addr);

    // Clean up
    pthread_join(thr, NULL);
    munmap(addr, PAGE_SIZE);
    close(uffd);

    return 0;
}

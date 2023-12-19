#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FILENAME "key_value_store.bin"
#define MAX_ENTRIES 1000
#define MAX_KEY_LENGTH 32
#define MAX_VALUE_LENGTH 256


struct KeyValue {
    int key;
    char value[MAX_VALUE_LENGTH];
};

int main() {

    int fd = open(FILENAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    if (ftruncate(fd, MAX_ENTRIES * sizeof(struct KeyValue)) == -1) {
        perror("ftruncate");
        exit(1);
    }

    struct KeyValue *kv_store = mmap(NULL, MAX_ENTRIES * sizeof(struct KeyValue), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (kv_store == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    close(fd);

    // Initialize the key-value store
    for (int i = 0; i < MAX_ENTRIES; ++i) {
        memset(kv_store[i].key, 0, MAX_KEY_LENGTH);
        memset(kv_store[i].value, 0, MAX_VALUE_LENGTH);
    }



    // Unmap the memory region
    if (munmap(kv_store, MAX_ENTRIES * sizeof(struct KeyValue)) == -1) {
        perror("munmap");
        exit(1);
    }

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

void invert_case(char* text) {
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = toupper(text[i]);
        } else if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = tolower(text[i]);
        }
    }
}

int main(int argc, char* argv[]) {
    int shmid, shmid1;
    key_t key = IPC_CREAT;
    char* shared_memory;
    char* shared_memory1;

    shmid = shmget(key, 1000, IPC_CREAT | 0666);
    shared_memory = (char*)shmat(shmid, NULL, 0);

    shmid1 = shmget(key + 1, 1000, IPC_CREAT | 0666);
    shared_memory1 = (char*)shmat(shmid1, NULL, 0);

    strcpy(shared_memory, argv[1]);

    int pid = fork();

    if (pid == 0) {
        invert_case(shared_memory);
        strcpy(shared_memory1, shared_memory);
    } else {
        wait(NULL);
        printf("%s\n", shared_memory1);
    }

    return 0;
}

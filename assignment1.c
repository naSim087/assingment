#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
#include <stdbool.h>

#define BUFFER 1000
#define TEXT 1000

int main() {
    int pipefd[2];
    pid_t pid;

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();
    if (pid == -1) {
        exit(1);
    } else if (pid == 0) {
        int n_sentc = 0, n_wrd = 0, n_chr = 0, n_schr = 0;
        bool wf = 0, sf = 0;
        char arr[BUFFER];
        int n = read(pipefd[0], arr, BUFFER);
        if (n == -1) {
            exit(1);
        }
        close(pipefd[0]);
        arr[n] = '\0';
        for (int i = 0; arr[i] != '\0'; i++) {
            if (isalnum(arr[i])) {
                n_chr++;
                if (!wf) {
                    n_wrd++;
                    wf = 1;
                }
            } else if (!isspace(arr[i])) {
                if (arr[i] == '.' || arr[i] == '!' || arr[i] == '?') n_sentc++;
                n_schr++;
                wf = 0;
                n_chr++;
                sf = 1;
            } else {
                wf = 0;
            }
        }
         write(pipefd[1], &n_chr, sizeof(int));
         write(pipefd[1], &n_schr, sizeof(int));
         write(pipefd[1], &n_wrd, sizeof(int));
        write(pipefd[1], &n_sentc, sizeof(int));
       
       
       
        close(pipefd[1]);
        exit(1);
    } else {
        int n_sentc = 0, n_wrd = 0, n_chr = 0, n_schr = 0;
        int wf = 0, sf = 0;
        char arr[TEXT];
        printf("Enter text: ");
        fgets(arr, TEXT, stdin);
        write(pipefd[1], arr, strlen(arr) + 1);
        close(pipefd[1]);
        wait(NULL);
         read(pipefd[0], &n_chr, sizeof(int));
         read(pipefd[0], &n_schr, sizeof(int));
          read(pipefd[0], &n_wrd, sizeof(int));
        read(pipefd[0], &n_sentc, sizeof(int));
       
        
       
        close(pipefd[0]);
        printf("Number of sentences: %d\n", n_sentc);
        printf("Number of words: %d\n", n_wrd);
        printf("Number of characters: %d\n", n_chr);
        printf("Number of special characters: %d\n", n_schr);
        exit(1);
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  
    int pipefd[2];
    pid_t pid;
   

    if (pipe(pipefd) == -1) {
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
         

         close(pipefd[1]);
        dup2(pipefd[0],0);
        close(pipefd[0]);
         execlp("wc", "wc", NULL);
         exit(EXIT_FAILURE);
    } else {
          printf("hello");
         close(pipefd[0]);
        dup2(pipefd[1], 1);
        close(pipefd[1]);
         execlp("ls", "ls", NULL);
         exit(EXIT_FAILURE);
       
    }

    return 0;
}

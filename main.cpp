#include <sys/types.h>
#include <sys/wait.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include "headers/list_directory_server.h"
#include "headers/client.h"

int main(int argc, char *argv[])
{
    int pipefd[2]; // 0 - read; 1 - write
    pid_t c_pid;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    c_pid = fork();
    int c_pid_state = 0;
    switch (c_pid) {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);
        case 0: {
            //Child proc
            //Close pipefd[1], here use only pipefd[0] read
            close(pipefd[1]);
            client c(pipefd[0]);
            c.out_pipe_data(STDOUT_FILENO);
        }
        default: {
            //Parent proc
            //Close pipefd[0], here use only pipefd[1] write
            close(pipefd[0]);
            list_directory_server lds(pipefd[1]);
            lds << argv[1];
            lds.fd_close();
            wait(&c_pid_state);
            printf("\nClose child with status: %i\n", c_pid_state / 256);
            exit(EXIT_SUCCESS);
        }
    }
}
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <cerrno>
#include "headers/message_sender.h"
#include "headers/message_reader.h"
#include "headers/d_watcher.h"

int main(int argc, char *argv[])
{
    int pipefd[2]; // 0 - read; 1 - write
    pid_t c_pid;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (pipe(pipefd) == -1) {
        perror(strerror(errno));
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
            message_reader c(pipefd[0]);
            c.out_pipe_data(STDOUT_FILENO);
            c.fd_close();
            exit(EXIT_SUCCESS);
        }
        default: {
            //Parent proc
            //Close pipefd[0], here use only pipefd[1] write
            close(pipefd[0]);
            message_sender lds(pipefd[1]);
            d_watcher dw(argv[1]);
            lds << dw.listing();
            lds.fd_close();
            wait(&c_pid_state);
            switch(c_pid_state) {
                case EXIT_SUCCESS:
                    //That's not ok, but still here for debug
                    printf("\n--- Child process exited success! ---\n");
                    break;
                default:
                    fprintf(stderr, "Child process exited with status %i", c_pid_state);
                    break;
            }
            exit(EXIT_SUCCESS);
        }
    }
}
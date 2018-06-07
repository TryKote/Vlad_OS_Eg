//
// Created by kote on 07.06.18.
//

#include "../headers/message_sender.h"

message_sender::message_sender(int &write_pipefd) {
    m_write_pipefd = write_pipefd;
}

ssize_t *message_sender::operator<<(char *arg) {
    ssize_t st = write(m_write_pipefd, arg, strlen(arg));
    return reinterpret_cast<ssize_t*>(st);
}

void message_sender::fd_close() {
    close(m_write_pipefd);
}

message_sender::~message_sender() {
    close(m_write_pipefd);
    exit(EXIT_SUCCESS);
}
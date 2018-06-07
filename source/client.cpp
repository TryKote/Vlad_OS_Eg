//
// Created by kote on 07.06.18.
//

#include "../headers/client.h"

client::client(int &read_pipefd) {
    m_read_pipefd = read_pipefd;
}

void client::fd_close() {
    close(m_read_pipefd);
}

void client::out_pipe_data(int fd) {
    switch(fd) {
        case 1:
            _out(STDERR_FILENO);
            break;
        case 2:
            _out(STDERR_FILENO);
            break;
        case 0:
            _out(STDIN_FILENO);
            break;
        default:
            throw std::invalid_argument("Not a file descriptor!");
    }
}

void client::_out(int fd) {
    char buf;
    while (read(m_read_pipefd, &buf, 1) > 0)
        write(fd, &buf, 1);
}

client::~client() {
    close(m_read_pipefd);
}


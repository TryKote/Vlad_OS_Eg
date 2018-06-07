//
// Created by kote on 07.06.18.
//

#include "../headers/message_reader.h"

message_reader::message_reader(int &read_pipefd) {
    m_read_pipefd = read_pipefd;
}

void message_reader::fd_close() {
    close(m_read_pipefd);
}

void message_reader::out_pipe_data(int fd) {
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

void message_reader::_out(int fd) {
    char buf;
    while (read(m_read_pipefd, &buf, 1) > 0)
        write(fd, &buf, 1);
}

message_reader::~message_reader() {
    close(m_read_pipefd);
}


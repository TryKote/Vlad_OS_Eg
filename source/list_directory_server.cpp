//
// Created by kote on 07.06.18.
//

#include "../headers/list_directory_server.h"

list_directory_server::list_directory_server(int &write_pipefd) {
    m_write_pipefd = write_pipefd;
}

ssize_t *list_directory_server::operator<<(char *arg) {
    return reinterpret_cast<ssize_t *>(write(m_write_pipefd, arg, strlen(arg)));
}

void list_directory_server::fd_close() {
    close(m_write_pipefd);
}

list_directory_server::~list_directory_server() {
    close(m_write_pipefd);
    exit(EXIT_SUCCESS);
}

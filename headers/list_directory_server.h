//
// Created by kote on 07.06.18.
//
#include <cstring>
#include <unistd.h>
#include <stdexcept>

#ifndef VLAD_OS_EG_LIST_DIRECTORY_SERVER_H
#define VLAD_OS_EG_LIST_DIRECTORY_SERVER_H

class list_directory_server {
public:
    explicit list_directory_server(int &write_pipefd);
    ~list_directory_server();
    void fd_close();

    ssize_t *operator<<(char* arg);
private:
    int m_write_pipefd;

};


#endif //VLAD_OS_EG_LIST_DIRECTORY_SERVER_H

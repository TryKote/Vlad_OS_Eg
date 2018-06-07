//
// Created by kote on 07.06.18.
//
#include <cstring>
#include <unistd.h>
#include <stdexcept>
#include "d_watcher.h"

#ifndef VLAD_OS_EG_LIST_DIRECTORY_SERVER_H
#define VLAD_OS_EG_LIST_DIRECTORY_SERVER_H

class message_sender {
    /* Send message in pipe channel */
public:
    explicit message_sender(int &write_pipefd);
    ~message_sender();
    void fd_close();
    ssize_t *operator<<(char* arg);

private:
    int m_write_pipefd;

};


#endif //VLAD_OS_EG_LIST_DIRECTORY_SERVER_H

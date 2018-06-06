//
// Created by kote on 07.06.18.
//

#include <unistd.h>
#include <stdexcept>

#ifndef VLAD_OS_EG_CLIENT_H
#define VLAD_OS_EG_CLIENT_H


class client {
public:
    explicit client(int& read_pipefd);
    void out_pipe_data(int fd);
    void fd_close();
    ~client();

private:
    int m_read_pipefd;

    void _out(int fd);
};


#endif //VLAD_OS_EG_CLIENT_H

//
// Created by kote on 07.06.18.
//

#include <stdexcept>
#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <cerrno>

#ifndef VLAD_OS_EG_D_WATCHER_H
#define VLAD_OS_EG_D_WATCHER_H


class d_watcher {
public:
    explicit d_watcher(const char dir[]);
    char* listing();
    void show();

private:
    char* _parse(struct dirent *pDirent);
    char* m_working_directory;

};


#endif //VLAD_OS_EG_D_WATCHER_H

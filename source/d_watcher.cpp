//
// Created by kote on 07.06.18.
//

#include <sstream>
#include "../headers/d_watcher.h"

d_watcher::d_watcher(const char dir[]) {
    m_working_directory = const_cast<char *>(dir);
//    std::cout << "Dir: " << m_working_directory << std::endl;
}

void d_watcher::show() {
    std::cout << "Dir: " << m_working_directory << std::endl;
}

char *d_watcher::listing() {
    struct dirent *pDirent;
    DIR *pDir;

    pDir = opendir(m_working_directory);

    if (pDir == nullptr) {
        perror(strerror(errno));
        throw std::runtime_error(strerror(errno));
    }

    std::stringstream directory_listing;
    while ((pDirent = readdir(pDir)) != nullptr) {
        directory_listing << _parse(pDirent) << std::endl;
    }
    closedir(pDir);

    char* c_directory_listing = new char[directory_listing.str().length()];
    strcpy(c_directory_listing, directory_listing.str().c_str());
    return c_directory_listing;
}

char *d_watcher::_parse(struct dirent *pDirent) {
    std::stringstream output_string;
    struct stat sfile;
    stat(pDirent->d_name, &sfile);

    output_string << pDirent->d_name << "\t";
    output_string << sfile.st_mtim.tv_sec << "\t";
    output_string << sfile.st_size << "\t";

    switch (pDirent->d_type) {
        case DT_DIR:
            output_string << "D" << "\t";
            break;
        case DT_BLK:
            output_string << "B" << "\t";
            break;
        case DT_LNK:
            output_string << "L" << "\t";
            break;
        case DT_REG:
            output_string << "R" << "\t";
            break;
        case DT_SOCK:
            output_string << "S" << "\t";
            break;
        case DT_FIFO:
            output_string << "P" << "\t";
            break;
        case DT_UNKNOWN:
            output_string << "?" << "\t";
            break;
        default:
            throw std::invalid_argument("Incorrect file type!");
    }

    const unsigned long size = output_string.str().length();
    char* c_output_string = new char[output_string.str().length()];
    strcpy(c_output_string, output_string.str().c_str());

    return c_output_string;
}

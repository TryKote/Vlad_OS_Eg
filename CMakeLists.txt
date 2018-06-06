cmake_minimum_required(VERSION 3.8)
project(Vlad_OS_Eg)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        main.cpp source/list_directory_server.cpp headers/list_directory_server.h source/client.cpp headers/client.h)
add_executable(Vlad_OS_Eg ${SOURCE_FILES})
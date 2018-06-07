cmake_minimum_required(VERSION 3.8)
project(Vlad_OS_Eg)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        main.cpp source/message_sender.cpp headers/message_sender.h source/message_reader.cpp headers/message_reader.h source/d_watcher.cpp headers/d_watcher.h)
add_executable(Vlad_OS_Eg ${SOURCE_FILES})
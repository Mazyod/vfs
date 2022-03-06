cmake_minimum_required(VERSION 3.18)
project(vfs)

set(CMAKE_CXX_STANDARD 20)

add_executable(app main.cpp src/commandline_parser.cpp src/commandline_parser.h include/strings.h include/strings.cpp src/inmemory_file_system.cpp src/inmemory_file_system.h src/file_system_operations.cpp src/file_system_operations.h src/application.cpp src/application.h include/file_system.h src/file_system/tree.cpp src/file_system/tree.h)

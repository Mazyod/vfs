cmake_minimum_required(VERSION 3.18)
project(vfs)

set(CMAKE_CXX_STANDARD 20)

add_executable(app main.cpp src/CommandlineParser.cpp src/CommandlineParser.h include/strings.h include/strings.cpp src/TreeFileSystem.cpp src/TreeFileSystem.h src/FileSystemOperations.cpp src/FileSystemOperations.h src/Application.cpp src/Application.h include/file_system.h)

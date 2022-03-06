cmake_minimum_required(VERSION 3.18)
project(vfs)

set(CMAKE_CXX_STANDARD 20)

add_executable(app main.cpp src/CommandParser.cpp src/CommandParser.h include/strings.h include/strings.cpp src/FileSystem.cpp src/FileSystem.h src/CommandValidation.h)

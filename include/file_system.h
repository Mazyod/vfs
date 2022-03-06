//
// Created by suraj on 3/6/22.
//

#ifndef VFS_FILE_SYSTEM_H
#define VFS_FILE_SYSTEM_H

#include<string>

//File and Directory Nodes
enum NodeType {
    File,
    DIRECTORY
};

//Define the operations a file system should implement
// Currently InmemoryFileSystem is implemented but if a new file system based on
class FileSystemInterface {
public:
    virtual void create_directory(std::string path) = 0;

    virtual void touch_file(std::string path) = 0;

    virtual void find_path(std::string path) = 0;

    virtual void find_between_path(std::string first, std::string second) = 0;
};

#endif //VFS_FILE_SYSTEM_H

//
// Created by suraj on 3/6/22.
//

#ifndef VFS_INMEMORY_FILE_SYSTEM_H
#define VFS_INMEMORY_FILE_SYSTEM_H

#include<string>
#include<vector>
#include<iostream>
#include "../include/strings.h"
#include "../include/file_system.h"
#include "file_system/tree.h"

//InmemoryFileSystem is a class that implements the file system interface
class InmemoryFileSystem : public FileSystemInterface {
    Tree root;
public:

    InmemoryFileSystem() : root(Tree("", DIRECTORY)) {}

    void addPath(std::string path);

    void touch_file(std::string path);

    void find_path(std::string path);

    void find_between_path(std::string first, std::string second);

};


#endif //VFS_INMEMORY_FILE_SYSTEM_H

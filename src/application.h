//
// Created by suraj on 3/6/22.
//

#ifndef VFS_APPLICATION_H
#define VFS_APPLICATION_H

#include "inmemory_file_system.h"
#include "file_system_operations.h"
#include "commandline_parser.h"

class Application {
    FileSystemInterface *file_system;
    Operation *operation;

    void setOperation(ParsedCommand parsedCommand);


public:
//    Construct an application injecting a file system
    Application(FileSystemInterface &file_system) {
        this->file_system = &file_system;
    }

//    Run an application
    void run();
};

#endif //VFS_APPLICATION_H

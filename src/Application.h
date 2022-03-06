//
// Created by suraj on 3/6/22.
//

#ifndef VFS_APPLICATION_H
#define VFS_APPLICATION_H

#include "FileSystem.h"
#include "FileSystemOperations.h"
#include "CommandlineParser.h"

class Application {
    FileSystemInterface *file_system;
    Operation *operation;
public:
    Application(FileSystemInterface &file_system) {
        this->file_system = &file_system;
    }

    void setOperation(ParsedCommand parsedCommand);

    void run();
};

#endif //VFS_APPLICATION_H

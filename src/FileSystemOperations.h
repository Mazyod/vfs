//
// Created by suraj on 3/6/22.
//

#ifndef VFS_FILESYSTEMOPERATIONS_H
#define VFS_FILESYSTEMOPERATIONS_H

#include "CommandlineParser.h"
#include "TreeFileSystem.h"

#define OPERATION_SUCCESSFUL 0;
#define OPERATION_EXIT 1;

class Operation {
public:
    virtual int execute(ParsedCommand parsedCommand, FileSystemInterface *file_system) = 0;
};

class MakeDirectoryOperation : public Operation {
    bool validate(ParsedCommand command) const {
        return command.command == "mkdir" and command.args.size() == 1;
    }

public:
    int execute(ParsedCommand parsedCommand, FileSystemInterface *file_system) override;
};

class TouchFileOperation : public Operation {
    bool validate(ParsedCommand command) const {
        return command.command == "touch" and command.args.size() == 1;
    }

public:
    int execute(ParsedCommand parsedCommand, FileSystemInterface *file_system) override;
};

class FindFileDirectoryOperation : public Operation {

    bool validate(ParsedCommand command) const {
        return command.command == "find" and (command.args.size() >= 1 or command.args.size() <= 2);
    }

public:
    int execute(ParsedCommand parsedCommand, FileSystemInterface *file_system) override;
};

class ExitOperation : public Operation {
public:
    int execute(ParsedCommand parsedCommand, FileSystemInterface *file_system) override {
        return OPERATION_EXIT;
    }
};

class InvalidOperation : public Operation {
public:
    int execute(ParsedCommand parsedCommand, FileSystemInterface *file_system) override {
        std::cout << "Invalid Command: " << parsedCommand.command << std::endl;
        return OPERATION_SUCCESSFUL;
    }
};

#endif //VFS_FILESYSTEMOPERATIONS_H

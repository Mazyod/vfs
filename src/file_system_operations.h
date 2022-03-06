//
// Created by suraj on 3/6/22.
//

#ifndef VFS_FILE_SYSTEM_OPERATIONS_H
#define VFS_FILE_SYSTEM_OPERATIONS_H

#include "commandline_parser.h"
#include "inmemory_file_system.h"

#define OPERATION_SUCCESSFUL 0
#define OPERATION_EXIT 1

//Operation is an interface which defines the commands which can be implemented
class Operation {
protected:
//    Validate the command passed in
    virtual bool validate(ParsedCommand command) = 0;

public:
//    Execute a given command on a file system
    virtual int execute(ParsedCommand parsedCommand, FileSystemInterface *file_system) = 0;
};

//Operation to create a new directory
class MakeDirectoryOperation : public Operation {
    bool validate(ParsedCommand command) {
        return command.command == "mkdir" and command.args.size() == 1;
    }

public:
    int execute(ParsedCommand parsedCommand, FileSystemInterface *file_system) override;
};

//Operation to create a new file
class TouchFileOperation : public Operation {
    bool validate(ParsedCommand command) {
        return command.command == "touch" and command.args.size() == 1;
    }

public:
    int execute(ParsedCommand parsedCommand, FileSystemInterface *file_system) override;
};

//Find a file or directory operation
class FindFileDirectoryOperation : public Operation {
    bool validate(ParsedCommand command) {
        return command.command == "find" and (command.args.size() >= 1 or command.args.size() <= 2);
    }

public:
    int execute(ParsedCommand parsedCommand, FileSystemInterface *file_system) override;
};

//Exit the program operation
class ExitOperation : public Operation {
    bool validate(ParsedCommand command) { return command.command == "exit"; }

public:
    int execute(ParsedCommand parsedCommand, FileSystemInterface *file_system) override {
        return OPERATION_EXIT;
    }
};

//Invalid operation if the operation is not valid
class InvalidOperation : public Operation {
    bool validate(ParsedCommand command) { return true; }

public:
    int execute(ParsedCommand parsedCommand, FileSystemInterface *file_system) override {
        std::cout << "Invalid Command: " << parsedCommand.command << std::endl;
        return OPERATION_SUCCESSFUL;
    }
};

#endif //VFS_FILE_SYSTEM_OPERATIONS_H

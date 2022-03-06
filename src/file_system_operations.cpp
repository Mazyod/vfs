//
// Created by suraj on 3/6/22.
//

#include "file_system_operations.h"

int MakeDirectoryOperation::execute(ParsedCommand parsedCommand, FileSystemInterface *file_system) {
    bool valid = validate(parsedCommand);
    if (valid) {
        file_system->addPath(parsedCommand.args.at(0));
    } else {
        std::cout << "mkdir: command not entered correctly" << std::endl;
    }
    return OPERATION_SUCCESSFUL;
}

int TouchFileOperation::execute(ParsedCommand parsedCommand, FileSystemInterface *file_system) {
    bool valid = validate(parsedCommand);
    if (valid) {
        std::string path = parsedCommand.args.at(0);
        file_system->touch_file(path);
    } else {
        std::cout << "Invalid: " << parsedCommand.command << " does not exist" << std::endl;
    }
    return OPERATION_SUCCESSFUL;
}


int FindFileDirectoryOperation::execute(ParsedCommand parsedCommand, FileSystemInterface *file_system) {
    bool valid = validate(parsedCommand);
    if (valid) {
        std::string path = parsedCommand.args.at(0);
        file_system->touch_file(path);
    } else {
        std::cout << "Invalid: " << parsedCommand.command << " does not exist" << std::endl;
    }
    return OPERATION_SUCCESSFUL;
}
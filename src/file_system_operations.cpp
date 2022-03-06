//
// Created by suraj on 3/6/22.
//

#include "file_system_operations.h"

int MakeDirectoryOperation::execute(ParsedCommand parsedCommand, FileSystemInterface *file_system) {
    bool valid = validate(parsedCommand);
    if (valid) {
        file_system->create_directory(parsedCommand.args.at(0));
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
        if (parsedCommand.args.size() == 1) {
            std::string path = parsedCommand.args.at(0);
            file_system->find_path(path);
        } else {
            std::string path1 = parsedCommand.args.at(0);
            std::string path2 = parsedCommand.args.at(1);
            file_system->find_between_path(path1, path2);
        }
    } else {
        std::cout << "Invalid: " << parsedCommand.command << " does not exist" << std::endl;
    }
    return OPERATION_SUCCESSFUL;
}
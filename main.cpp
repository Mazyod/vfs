#include <iostream>
#include <string>
#include "src/CommandParser.h"
#include "src/CommandValidation.h"
#include "src/FileSystem.h"

int main() {
    std::string commandString;
    std::cout << "Supported commands: mkdir, touch, find, exit" << std::endl;
    TreeNode treeNode("", directory);
    Tree file_system(treeNode);
    do {
        std::cout << "Command: ";
        std::getline(std::cin, commandString);

        CommandParser commandParser;
        ParsedCommand parsedCommand = commandParser.parseString(commandString);

        if (parsedCommand.command == "mkdir") {
            bool valid = validate_mkdir(parsedCommand);
            if (valid) {
                file_system.addPath(parsedCommand.args.at(0));
            } else {
                std::cout << "mkdir: command not entered correctly" << std::endl;
            }
        } else if (parsedCommand.command == "touch") {
            bool valid = validate_touch(parsedCommand);
            if (valid) {
                std::string path = parsedCommand.args.at(0);
                file_system.touch_file(path);
            } else {
                std::cout << "Invalid: " << commandString << " does not exist" << std::endl;
            }
        } else if (parsedCommand.command == "find") {
            bool valid = validate_find(parsedCommand);
            if (valid) {
                if (parsedCommand.args.size() == 1) {
                    std::string path = parsedCommand.args.at(0);
                    file_system.find_path(path);
                } else {
                    std::string path1 = parsedCommand.args.at(0);
                    std::string path2 = parsedCommand.args.at(1);
                    file_system.find_between_path(path1, path2);
                }
            }
        } else if (parsedCommand.command == "exit") {
            break;
        } else {
            std::cout << "Invalid Command: " << commandString << std::endl;
        }

    } while (commandString != "exit");


    return 0;
}

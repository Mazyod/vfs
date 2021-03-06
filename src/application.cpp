//
// Created by suraj on 3/6/22.
//
#include "application.h"

//Set the operation from a parsedCommand into an Operation
void Application::setOperation(ParsedCommand parsedCommand) {
    if (parsedCommand.command == "mkdir") {
        MakeDirectoryOperation makeDirectory;
        operation = &makeDirectory;
    } else if (parsedCommand.command == "touch") {
        TouchFileOperation touchFile;
        operation = &touchFile;
    } else if (parsedCommand.command == "find") {
        FindFileDirectoryOperation findFileDirectory;
        operation = &findFileDirectory;
    } else if (parsedCommand.command == "exit") {
        ExitOperation exitOperation;
        operation = &exitOperation;
    } else {
        InvalidOperation invalidOperation;
        operation = &invalidOperation;
    }
}

//Run the application and read commands from the user
void Application::run() {
    std::string commandString;
    CommandlineParser commandParser;
    std::cout << "Supported commands: mkdir, touch, find, exit" << std::endl;
    int running = OPERATION_SUCCESSFUL;
    do {
        std::cout << "Command: ";
        std::getline(std::cin, commandString);

        auto parsedCommand = commandParser.parseString(commandString);
        setOperation(parsedCommand);
        running = operation->execute(parsedCommand, file_system);
    } while (running == OPERATION_SUCCESSFUL);
};


//
// Created by suraj on 3/6/22.
//
#ifndef VFS_COMMANDPARSER_H
#define VFS_COMMANDPARSER_H


#include "../include/strings.h"
#include <string>
#include <vector>

struct ParsedCommand {
    std::string command;
    std::vector<std::string> args;
};

class CommandParserInterface {
public:
    virtual ParsedCommand parseString(std::string line) {}
};

class CommandParser : public CommandParserInterface {
public:
    ParsedCommand parseString(std::string line);
};

#endif //VFS_COMMANDPARSER_H

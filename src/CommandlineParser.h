//
// Created by suraj on 3/6/22.
//
#ifndef VFS_COMMANDLINEPARSER_H
#define VFS_COMMANDLINEPARSER_H


#include "../include/strings.h"
#include <string>
#include <vector>

struct ParsedCommand {
    std::string command;
    std::vector<std::string> args;
};

class StringParser {
public:
    virtual ParsedCommand parseString(std::string line) = 0;
};

class CommandlineParser : public StringParser {
public:
    ParsedCommand parseString(std::string line);
};

#endif //VFS_COMMANDLINEPARSER_H

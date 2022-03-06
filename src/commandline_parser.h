//
// Created by suraj on 3/6/22.
//
#ifndef VFS_COMMANDLINE_PARSER_H
#define VFS_COMMANDLINE_PARSER_H


#include "../include/strings.h"
#include <string>
#include <vector>

//ParsedCommand is a struct used to construct a command and arguments list.
struct ParsedCommand {
    std::string command;
    std::vector<std::string> args;
};

//StringParser is an interface which can parse String
class StringParser {
public:
    virtual ParsedCommand parseString(std::string line) = 0;
};

//CommandlineParser is a concrete implementation of the StringParser Interface
class CommandlineParser : public StringParser {
public:
    ParsedCommand parseString(std::string line);
};

#endif //VFS_COMMANDLINE_PARSER_H

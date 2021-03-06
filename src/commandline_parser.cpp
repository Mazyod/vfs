//
// Created by suraj on 3/6/22.
//

#include "commandline_parser.h"

//Parses a string into a ParsedCommand struct
// "make 1/2/3" => ParsedCommand(std::string("mkdir"), std::vector<string>("1/2/3"))
ParsedCommand CommandlineParser::parseString(std::string line) {
    ParsedCommand command;
    std::string trimmedLine = trim(line);
    std::vector<std::string> splits;
    split(trimmedLine, splits, ' ');
    command.command = splits.at(0);
    splits.erase(splits.begin());
    command.args = splits;
    return command;
};
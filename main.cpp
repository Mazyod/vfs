#include <iostream>
#include <string>
#include <vector>

std::string ltrim(std::string s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string rtrim(std::string s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

std::string trim(std::string s) {
    return ltrim(rtrim(s));
}

size_t split(const std::string &txt, std::vector<std::string> &strs, char ch) {
    size_t pos = txt.find(ch);
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while (pos != std::string::npos) {
        strs.push_back(txt.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;

        pos = txt.find(ch, initialPos);
    }

    // Add the last one
    strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

    return strs.size();
}

enum NodeType{
    file,
    directory
};

class TreeNode {
public:
    std::string name;
    int level;
    NodeType nodeType;
    std::vector<TreeNode> children;

    TreeNode() {
        this->name = "";
        this->level = 0;
        this->nodeType = directory;
    }

    std::string getName() {
        return name;
    }
};

struct ParsedCommand {
    std::string command;
    std::vector<std::string> args;
};

class CommandParser {
public:
    ParsedCommand parseString(std::string line) {
        struct ParsedCommand command;
        std::string trimmedLine = trim(line);
        std::vector<std::string> splits;
        split(trimmedLine, splits, ' ');
        command.command = splits.at(0);
        splits.erase(splits.begin());
        command.args = splits;
        return command;
    }
};

bool validate_mkdir(ParsedCommand basicString);

bool create_dir(std::string path);

bool validate_touch(ParsedCommand command);

bool touch_file(std::string path);

bool validate_find(ParsedCommand path);

bool find_path(std::string path);

int main() {
    std::string commandString;
    std::cout << "Supported commands: mkdir, touch, find, exit" << std::endl;
    TreeNode file_system;
    do {
        std::cout << "Command: ";
        std::getline(std::cin, commandString);

        CommandParser commandParser;
        ParsedCommand parsedCommand = commandParser.parseString(commandString);

        if (parsedCommand.command == "mkdir") {
            bool valid = validate_mkdir(parsedCommand);
            if (valid) {
                bool created = create_dir("test");
                if (created) {
                    std::cout << commandString << " has been created" << std::endl;
                }
            } else {
                std::cout << "mkdir: command not entered correctly" << std::endl;
            }
        } else if (parsedCommand.command == "touch") {
            bool valid = validate_touch(parsedCommand);
            if (valid) {
                std::string path = parsedCommand.args.at(0);
                bool created = touch_file(path);
                if (created) {
                    std::cout << path << " has been created" << std::endl;
                }
            } else {
                std::cout << "Invalid: " << commandString << " does not exist" << std::endl;
            }
        } else if (parsedCommand.command == "touch") {
            bool valid = validate_find(parsedCommand);
            if (valid) {
                bool found = find_path(commandString);
                if (found) {

                } else {
                    std::cout << commandString << " cannot be found" << std::endl;
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

bool find_path(std::string path) {
    return true;
}

bool validate_find(ParsedCommand command) {
    return command.command == "find" and (command.args.size() >= 1 or command.args.size() <= 2);
}

bool touch_file(std::string path) {
    return true;
}

bool validate_touch(ParsedCommand command) {
    return command.command == "touch" and command.args.size() == 1;
}

bool create_dir(std::string path) {

}

bool validate_mkdir(ParsedCommand command) {
    return command.command == "mkdir" and command.args.size() == 1;
}

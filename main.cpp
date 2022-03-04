#include <iostream>
#include <string>
#include <vector>

std::string ltrim(std::string s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    [](int c) { return !std::isspace(c); }));
    return s;
}

// trim from end
std::string rtrim(std::string s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         [](int c) { return !std::isspace(c); }).base(), s.end());
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

enum NodeType {
    file,
    directory
};;

class TreeNode {
public:
    std::string name;
    NodeType nodeType;
    std::vector<TreeNode> children;

    TreeNode(std::string name) {
        this->name = name;
        this->nodeType = directory;
    }

    std::string getName() {
        return name;
    }

    void create_dir(std::vector<std::string> *paths) {
        while (!paths->empty()) {
            auto currentPath = paths->begin();
            TreeNode treeNode(*currentPath);
            auto child = std::find_if(this->children.begin(), this->children.end(),
                                      [&currentPath](TreeNode c) { return c.name == *currentPath; });

            paths->erase(paths->begin(), paths->begin() + 1);
            if (child == this->children.end()) {
                std::cout << treeNode.name << " directory created" << std::endl;
                treeNode.create_dir(paths);
                this->children.push_back(treeNode);
            } else {
                (*child).create_dir(paths);
            }
        }
    }
};


class Tree {
public:
    TreeNode root;

    Tree(TreeNode root) : root(root) {
        this->root = root;
    }

    void addPath(std::string path) {
        std::vector<std::string> pathVector;
        split(path, pathVector, '/');
        this->root.create_dir(&pathVector);
    }


    void touch_file(std::string path){

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


bool validate_touch(ParsedCommand command);

bool validate_find(ParsedCommand path);

bool find_path(std::string path);

int main() {
    std::string commandString;
    std::cout << "Supported commands: mkdir, touch, find, exit" << std::endl;
    TreeNode treeNode("");
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

bool validate_touch(ParsedCommand command) {
    return command.command == "touch" and command.args.size() == 1;
}

bool validate_mkdir(ParsedCommand command) {
    return command.command == "mkdir" and command.args.size() == 1;
}

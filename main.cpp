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

    TreeNode(std::string name, NodeType nodeType) {
        this->name = name;
        this->nodeType = nodeType;
    }

    std::string getName() {
        return name;
    }

    void create_dir(std::vector<std::string> *paths) {
        while (!paths->empty()) {
            auto currentPath = paths->begin();
            TreeNode treeNode(*currentPath, directory);
            auto child = std::find_if(this->children.begin(), this->children.end(),
                                      [&currentPath](TreeNode c) { return c.name == *currentPath; });

            paths->erase(paths->begin(), paths->begin() + 1);
            if (child == this->children.end()) {
                std::cout << treeNode.name << " directory created" << std::endl;
                treeNode.create_dir(paths);
                this->children.push_back(treeNode);
            } else {
                if (child->nodeType == file) {
                    std::cout << "Invalid: Cannot create " << paths->back() << " under the file " << child->name
                              << std::endl;
                    paths->erase(paths->begin(), paths->end());
                    return;
                }
                (*child).create_dir(paths);
            }
        }
    }

    void create_file(std::vector<std::string> *paths) {
        while (!paths->empty()) {
            auto currentPath = paths->begin();
            TreeNode treeNode(*currentPath, file);
            auto child = std::find_if(this->children.begin(), this->children.end(),
                                      [&currentPath](TreeNode c) { return c.name == *currentPath; });
            if (child != this->children.end()) {
                if (child->nodeType == file) {
                    std::cout << "Cannot create file " << paths->back() << " under the file " << *currentPath
                              << std::endl;
                    return;
                } else {
                    if (paths->size() == 1) {
                        std::cout << "Cannot create file " << paths->back() << " under the folder with same name "
                                  << *currentPath << std::endl;
                        paths->erase(paths->begin(), paths->end());
                        return;
                    }
                    paths->erase(paths->begin(), paths->begin() + 1);
                    (*child).create_file(paths);
                }
            } else if (paths->size() == 1) {
                std::cout << paths->front() << " has been created" << std::endl;
                paths->erase(paths->begin(), paths->end());
                this->children.push_back(treeNode);
                return;
            }
        }
    }

    bool find_path(std::string name, TreeNode root, std::vector<std::string> &path) {
        if (name == root.name) {
            return true;
        }
        for (TreeNode child: root.children) {
            bool found = find_path(name, child, path);
            if (found) {
                path.push_back(child.name);
                return found;
            }
        }

        return !path.empty();
    }

    bool path_between(std::string first, std::string second, TreeNode root, std::vector<std::string> &path) {
        std::vector<std::string> pathFirst;
        bool foundFirst = find_path(first, root, pathFirst);
        if (!foundFirst) return false;

        std::vector<std::string> pathSecond;
        auto child = std::find_if(root.children.begin(), root.children.end(),
                                  [&pathFirst](TreeNode c) { return c.name == pathFirst.back(); });
        bool foundSecond = find_path(second, *child, pathSecond);
        if (!foundSecond) return false;


        for (auto f = pathFirst.begin(); f != pathFirst.end(); f++) {
            for (auto p = pathSecond.rbegin(); p != pathSecond.rend(); p++) {
                if (*f == *p) {
                    path.insert(path.end(), pathFirst.begin(), f);
                    path.insert(path.end(), p,pathSecond.rend());
                    return true;
                }
            }
        }


        return false;
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

    void touch_file(std::string path) {
        std::vector<std::string> pathVector;
        split(path, pathVector, '/');
        this->root.create_file(&pathVector);
    }

    void find_path(std::string path) {
        std::vector<std::string> pathVector;
        split(path, pathVector, '/');
        std::vector<std::string> pathV;
        auto destination = pathVector.back();
        this->root.find_path(destination, this->root, pathV);
        if (pathV.empty()) {
            std::cout << destination << " cannot be found" << std::endl;
        } else {
            std::cout << "Found: ";
            for (auto it = pathV.rbegin(); it != pathV.rend(); ++it) {
                std::cout << *it;
                if (it + 1 != pathV.rend()) {
                    std::cout << " - ";
                }
            }
            std::cout << std::endl;
        }
    }

    void find_between_path(std::string first, std::string second) {
        std::vector<std::string> pathV;
        this->root.path_between(first, second, this->root, pathV);
        if (pathV.empty()) {
            std::cout << "No path can be found between " << first << " and " << second << std::endl;
        } else {
            for (auto it = pathV.begin(); it != pathV.end(); ++it) {
                std::cout << *it;
                if (it + 1 != pathV.end()) {
                    std::cout << " - ";
                }
            }
            std::cout << std::endl;
        }
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

bool validate_find(ParsedCommand command) {
    return command.command == "find" and (command.args.size() >= 1 or command.args.size() <= 2);
}

bool validate_touch(ParsedCommand command) {
    return command.command == "touch" and command.args.size() == 1;
}

bool validate_mkdir(ParsedCommand command) {
    return command.command == "mkdir" and command.args.size() == 1;
}

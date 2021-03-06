//
// Created by suraj on 3/6/22.
//

#include "inmemory_file_system.h"
#include <algorithm>

//Splits the path string into a path vector and creates a new directory
void InmemoryFileSystem::create_directory(std::string path) {
    std::vector<std::string> paths;
    split(path, paths, '/');
    createDir(this->root, paths);
}

//Splits the path string into a path vector and creates a new file
void InmemoryFileSystem::touch_file(std::string path) {
    std::vector<std::string> paths;
    split(path, paths, '/');
    createFile(this->root, paths);
}

//Finds the path from the root to file
void InmemoryFileSystem::find_path(std::string path) {
    std::vector<std::string> pathVector;
    split(path, pathVector, '/');
    std::vector<std::string> pathV;
    auto destination = pathVector.back();
    this->root.find_path(destination, pathV);
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

//Finds the path from the file1 to file2
void InmemoryFileSystem::find_between_path(std::string first, std::string second) {
    std::vector<std::string> pathV;
    pathBetween(first, second, this->root, pathV);
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

//Recursively create node based on the path vector
void InmemoryFileSystem::createDir(Tree &node, std::vector<std::string> &paths) {
    while (!paths.empty()) {
        auto currentPath = paths.begin();
        Tree newNode(*currentPath, DIRECTORY);

        Tree *child = nullptr;
        node.get_child(*currentPath, child);

        int pathSize = paths.size();
        paths.erase(paths.begin(), paths.begin() + 1);

//        Check if node with the name exists
        if (child != nullptr) {

//            Override directory if folder with the same name is present
            if (child->nodeType ==DIRECTORY and pathSize == 0) {
                *child = newNode;
                return;
            }

//            Dont create a new directory if file with same name is present
            if (child->nodeType == File) {
                std::cout << "Invalid: Cannot create " << paths.back() << " under the File " << child->name
                          << std::endl;
//                stop iterating
                paths.erase(paths.begin(), paths.end());
                return;
            }

//            Create directories recursively
            createDir(*child, paths);
        } else {
//            If no node is present create directory recursively
            std::cout << newNode.name << " DIRECTORY created" << std::endl;
            createDir(newNode, paths);
            node.addTree(newNode);
        }
    }
}

//Recursively create node based on the path vector
void InmemoryFileSystem::createFile(Tree &node, std::vector<std::string> &paths) {
    while (!paths.empty()) {
        auto currentPath = paths.begin();
        Tree newNode(*currentPath, File);

        Tree *child = nullptr;
        node.get_child(*currentPath, child);

        if (child != nullptr) {
//            Override the existing file
            if (child->nodeType == File and child->name == *currentPath and paths.size() == 1) {
                *child = newNode;
                std::cout << *currentPath << " has been created" << std::endl;
                paths.erase(paths.begin(), paths.end());
                return;
            }
//            Cannot create file under another file
            if (child->nodeType == File) {
                std::cout << "Cannot create File " << paths.back() << " under the File " << *currentPath
                          << std::endl;
                paths.erase(paths.begin(), paths.end());
                return;
            }
//          Dont create file with the same name as directory
            if (paths.size() == 1) {
                std::cout << "Cannot create File " << paths.back() << " under the folder with same name "
                          << *currentPath << std::endl;
                paths.erase(paths.begin(), paths.end());
                return;
            }

//          Recursively create file
            paths.erase(paths.begin(), paths.begin() + 1);
            createFile(*child, paths);

        } else {
            if (paths.size() == 1) {
                std::cout << *currentPath << " has been created" << std::endl;
                node.addTree(newNode);
            } else {
                std::cout << "Invalid: " << *currentPath << " does not exist" << std::endl;
            }
            paths.erase(paths.begin(), paths.end());
            return;
        }
    }
}

//Recursively find path between two nodes with a shared root node
bool InmemoryFileSystem::pathBetween(std::string first, std::string second, Tree root, std::vector<std::string> &path) {
    std::vector<std::string> pathFirst;
    bool foundFirst = root.find_path(first, pathFirst);
    if (!foundFirst) return false;

    std::vector<std::string> pathSecond;
    auto child = std::find_if(root.children.begin(), root.children.end(),
                              [&pathFirst](Tree c) { return c.name == pathFirst.back(); });
    bool foundSecond = child->find_path(second, pathSecond);
    if (!foundSecond) return false;


    for (auto f = pathFirst.begin(); f != pathFirst.end(); f++) {
        for (auto p = pathSecond.rbegin(); p != pathSecond.rend(); p++) {
            if (*f == *p) {
                path.insert(path.end(), pathFirst.begin(), f);
                path.insert(path.end(), p, pathSecond.rend());
                return true;
            }
        }
    }

    return false;
}

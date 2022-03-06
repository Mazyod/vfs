//
// Created by suraj on 3/6/22.
//

#ifndef VFS_INMEMORY_FILE_SYSTEM_H
#define VFS_INMEMORY_FILE_SYSTEM_H

#include<string>
#include<vector>
#include<iostream>
#include "../include/strings.h"
#include "../include/file_system.h"


//Internal implementation of the tree backend file system
class Tree {
public:
    std::string name;
    NodeType nodeType;
    std::vector<Tree> children;

    Tree(std::string name, NodeType nodeType) {
        this->name = name;
        this->nodeType = nodeType;
    }

    void create_dir(std::vector<std::string> *paths) {
        while (!paths->empty()) {
            auto currentPath = paths->begin();
            Tree treeNode(*currentPath, DIRECTORY);
            auto child = std::find_if(this->children.begin(), this->children.end(),
                                      [&currentPath](Tree c) { return c.name == *currentPath; });

            paths->erase(paths->begin(), paths->begin() + 1);
            if (child == this->children.end()) {
                std::cout << treeNode.name << " DIRECTORY created" << std::endl;
                treeNode.create_dir(paths);
                this->children.push_back(treeNode);
            } else {
                if (child->nodeType == File) {
                    std::cout << "Invalid: Cannot create " << paths->back() << " under the File " << child->name
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
            Tree treeNode(*currentPath, File);
            auto child = std::find_if(this->children.begin(), this->children.end(),
                                      [&currentPath](Tree c) { return c.name == *currentPath; });
            if (child != this->children.end()) {
                if (child->nodeType == File) {
                    std::cout << "Cannot create File " << paths->back() << " under the File " << *currentPath
                              << std::endl;
                    return;
                } else {
                    if (paths->size() == 1) {
                        std::cout << "Cannot create File " << paths->back() << " under the folder with same name "
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

    bool find_path(std::string name, Tree root, std::vector<std::string> &path) {
        if (name == root.name) {
            return true;
        }
        for (Tree child: root.children) {
            bool found = find_path(name, child, path);
            if (found) {
                path.push_back(child.name);
                return found;
            }
        }

        return !path.empty();
    }

    bool path_between(std::string first, std::string second, Tree root, std::vector<std::string> &path) {
        std::vector<std::string> pathFirst;
        bool foundFirst = find_path(first, root, pathFirst);
        if (!foundFirst) return false;

        std::vector<std::string> pathSecond;
        auto child = std::find_if(root.children.begin(), root.children.end(),
                                  [&pathFirst](Tree c) { return c.name == pathFirst.back(); });
        bool foundSecond = find_path(second, *child, pathSecond);
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

};

//InmemoryFileSystem is a class that implements the file system interface
class InmemoryFileSystem : public FileSystemInterface {
    Tree root;
public:

    InmemoryFileSystem() : root(Tree("", DIRECTORY)) {}

    void addPath(std::string path);

    void touch_file(std::string path);

    void find_path(std::string path);

    void find_between_path(std::string first, std::string second);

};


#endif //VFS_INMEMORY_FILE_SYSTEM_H

//
// Created by suraj on 3/6/22.
//

#ifndef VFS_TREE_H
#define VFS_TREE_H


#include "../../include/file_system.h"
#include<string>
#include<vector>
#include<iostream>
#include<optional>
#include <functional>

//Internal implementation of the tree backend file system
class Tree {
public:
    std::string name;
    NodeType nodeType;
    std::vector <Tree> children;

    Tree(std::string name, NodeType nodeType) {
        this->name = name;
        this->nodeType = nodeType;
    }

    bool find_path(std::string name, std::vector <std::string> &path);

    void get_child(std::string name, Tree *&tree);

    void addTree(Tree &node);
};


#endif //VFS_TREE_H

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
    std::vector<Tree> children;

    Tree(std::string name, NodeType nodeType) {
        this->name = name;
        this->nodeType = nodeType;
    }

    bool find_path(std::string name, std::vector<std::string> &path) {
        if (name == this->name) {
            return true;
        }
        for (Tree child: this->children) {
            bool found = child.find_path(name, path);
            if (found) {
                path.push_back(child.name);
                return found;
            }
        }

        return !path.empty();
    }

    void get_child(std::string name, Tree *&tree) {
        tree = NULL;
        for (Tree &node: this->children) {
            if (node.name == name) {
                tree = &node;
            }
        }
    }

    void addTree(Tree &node) {
        this->children.push_back(node);
    }
};


#endif //VFS_TREE_H

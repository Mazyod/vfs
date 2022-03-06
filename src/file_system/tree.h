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

    void get_child(std::string name, Tree*& tree) {
        tree = NULL;
        for (Tree &node: this->children) {
            if (node.name == name) {
                tree = &node;
            }
        }
    }

    std::optional<Tree> get_child(std::string &name) {
        for (Tree &node: this->children) {
            if (node.name == name) {
                return node;
            }
        }
        return std::nullopt;

    }

    void addTree(Tree &node) {
        this->children.push_back(node);
    }
};


#endif //VFS_TREE_H

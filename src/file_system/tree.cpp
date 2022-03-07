//
// Created by suraj on 3/6/22.
//

#include "tree.h"

bool Tree::find_path(std::string name, std::vector<std::string> &path) {
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

void Tree::get_child(std::string name, Tree *&tree) {
    tree = NULL;
    for (Tree &node: this->children) {
        if (node.name == name) {
            tree = &node;
        }
    }
}

void Tree::addTree(Tree &node) {
    this->children.push_back(node);
}
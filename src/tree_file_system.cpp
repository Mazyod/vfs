//
// Created by suraj on 3/6/22.
//

#include "tree_file_system.h"

void TreeFileSystem::addPath(std::string path) {
    std::vector<std::string> pathVector;
    split(path, pathVector, '/');
    this->root.create_dir(&pathVector);
}

void TreeFileSystem::touch_file(std::string path) {
    std::vector<std::string> pathVector;
    split(path, pathVector, '/');
    this->root.create_file(&pathVector);
}

void TreeFileSystem::find_path(std::string path) {
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

void TreeFileSystem::find_between_path(std::string first, std::string second) {
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

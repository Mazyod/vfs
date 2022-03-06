//
// Created by suraj on 3/6/22.
//

#ifndef VFS_STRINGS_H
#define VFS_STRINGS_H

#include <string>
#include <vector>

//trim from the beginning
std::string ltrim(std::string s);

// trim from end
std::string rtrim(std::string s);

std::string trim(std::string s);

size_t split(const std::string &txt, std::vector<std::string> &strs, char ch);

#endif //VFS_STRINGS_H

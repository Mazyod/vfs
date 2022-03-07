//
// Created by suraj on 3/6/22.
//
//
// Created by suraj on 3/6/22.
//
#include <gtest/gtest.h>
#include<string>
#include "../src/application.cpp"
#include "../include/file_system.h"
#include "../src/commandline_parser.cpp"
#include "../src/file_system_operations.cpp"
#include "gmock/gmock.h"

using ::testing::AtLeast;

class MockFileSystem : public FileSystemInterface {
public:
    MOCK_METHOD(void, create_directory, (std::string path), (override));
    MOCK_METHOD(void, touch_file, (std::string path), (override));
    MOCK_METHOD(void, find_path, (std::string path), (override));
    MOCK_METHOD(void, find_between_path, (std::string first, std::string second), (override));
};

TEST(ApplicationsTest, ShouldCallCreateDirectory) {
//    MockFileSystem mockFileSystem;
//    Application application(mockFileSystem);
//    std::vector<std::string> args {""};
//    ParsedCommand command("mkdir", args);
//    application.setOperation(command);

}



cmake_minimum_required(VERSION 3.18)
project(vfs)

set(CMAKE_CXX_STANDARD 20)


add_executable(app main.cpp src/commandline_parser.cpp src/commandline_parser.h include/strings.h include/strings.cpp src/inmemory_file_system.cpp src/inmemory_file_system.h src/file_system_operations.cpp src/file_system_operations.h src/application.cpp src/application.h include/file_system.h src/file_system/tree.cpp src/file_system/tree.h)

if (test)

    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    add_executable( app_test test/strings_test.cpp)
    target_link_libraries(
            app_test
            gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(app_test)
endif ()
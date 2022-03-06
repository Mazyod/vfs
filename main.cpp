#include <string>
#include "src/FileSystem.h"
#include "src/Application.h"

int main() {
    FileSystem fileSystem;

    Application application(fileSystem);
    application.run();

    return EXIT_SUCCESS;
}

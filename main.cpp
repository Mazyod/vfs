#include <string>
#include "src/TreeFileSystem.h"
#include "src/Application.h"

int main() {
    TreeFileSystem fileSystem;

    Application application(fileSystem);
    application.run();

    return EXIT_SUCCESS;
}

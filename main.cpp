#include <string>
#include "src/tree_file_system.h"
#include "src/application.h"

int main() {
    TreeFileSystem fileSystem;

    Application application(fileSystem);
    application.run();

    return EXIT_SUCCESS;
}

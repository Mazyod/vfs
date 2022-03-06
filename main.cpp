#include <string>
#include "src/inmemory_file_system.h"
#include "src/application.h"

int main() {
    InmemoryFileSystem fileSystem;

    Application application(fileSystem);
    application.run();

    return EXIT_SUCCESS;
}

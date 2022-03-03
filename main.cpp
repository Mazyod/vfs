#include <iostream>
#include <string>

int main() {
    std::string command;
    std::cout << "Supported commands: mkdir, touch, find, exit" << std::endl;

    do{
        std::cout << "Command: ";
        std::cin >> command;

        if(command != "exit"){
            std::cout << "Invalid Command: " << command << std::endl;
        }

    }while(command != "exit");



    return 0;
}

#include <iostream>
#include <string>
#include <vector>


class TreeNode {
public:
    std::string name;
    std::vector<TreeNode> children;

    TreeNode() { this->name = ""; }

    std::string getName() {
        return name;
    }
};


bool validate_mkdir(std::string basicString);

bool create_dir(std::string basicString);

bool validate_touch(std::string basicString);

bool touch_file(std::string basicString);

bool validate_find(std::string basicString);

bool find_path(std::string basicString);

int main() {
    std::string command;
    std::cout << "Supported commands: mkdir, touch, find, exit" << std::endl;
    TreeNode file_system;
    do {
        std::cout << "Command: ";
        std::cin >> command;

        if (command.starts_with("mkdir")) {
            bool valid = validate_mkdir(command);
            if(valid){
                bool created = create_dir(command);
                if(created){
                    std::cout << command << " has been created" << std::endl;
                }
            }else{
                std::cout << "Directory already exists" << std::endl;
            }
        } else if (command.starts_with("touch")) {
            bool valid = validate_touch(command);
            if(valid){
                bool created = touch_file(command);
                if (created){
                    std::cout << command << " has been created" << std::endl;
                }
            }else{
                std::cout << "Invalid: " << command << " does not exist" << std::endl;
            }
        } else if (command.starts_with("find")) {
            bool valid = validate_find(command);
            if(valid){
                bool found = find_path(command);
                if(found){

                }else {
                    std::cout << command << " cannot be found" << std::endl;
                }
            }
        } else if (command.starts_with("exit")) {
            break;
        } else {
            std::cout << "Invalid Command: " << command << std::endl;
        }

    } while (command != "exit");


    return 0;
}

bool find_path(std::string basicString) {
    return true;
}

bool validate_find(std::string basicString) {
    return true;
}

bool touch_file(std::string basicString) {
    return true;
}

bool validate_touch(std::string basicString) {
    return true;
}

bool create_dir(std::string basicString) {

}

bool validate_mkdir(std::string command) {
    return true;
}

//
// Created by suraj on 3/6/22.
//


bool validate_find(ParsedCommand command) {
    return command.command == "find" and (command.args.size() >= 1 or command.args.size() <= 2);
}

bool validate_touch(ParsedCommand command) {
    return command.command == "touch" and command.args.size() == 1;
}

bool validate_mkdir(ParsedCommand command) {
    return command.command == "mkdir" and command.args.size() == 1;
}

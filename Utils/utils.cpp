#include <iostream>
#include "utils.h"
//
// Created by patrickgeorge1 on 5/5/20.
//

void CHECK(bool ok, std::string message) {
    // defensive programming
    if (ok) {
        std::cout << message << std::endl;
    }
}

int getSwitchCommand(std::string command) {
    if (command == "exit") return COMMAND_EXIT;
    else
        if (command == "register") return COMMAND_REGISTER;
        else
            if (command == "login") return COMMAND_LOGIN;
            else
                if (command == "enter_library") return COMMAND_ENTER_LIBRARY;
                else
                    if (command == "get_books") return COMMAND_GET_BOOKS;
                    else
                        if (command == "get_book") return COMMAND_GET_BOOK;
                        else
                            if (command == "add_book") return COMMAND_ADD_BOOK;
                            else
                                if (command == "delete_book") return COMMAND_DELETE_BOOK;
                                else
                                    if (command == "logut") return COMMAND_LOGOUT;
                                    else return COMMAND_INVALID;
}
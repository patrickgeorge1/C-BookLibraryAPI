#include <iostream>
#include <string>
#include "Utils/utils.h"
#include "Utils/api.h"

using namespace std;

int main() {

    bool isAuthenticated = false;
    string command;
    int status_sumary;

    do {
        cin >> command;
        switch (getSwitchCommand(command)) {
            case COMMAND_EXIT:
                exit(EXIT_SUCCESS);
                break;

            case COMMAND_REGISTER:
                status_sumary = proceed_register();
                break;

            case COMMAND_LOGIN:
                status_sumary = proceed_login();
                isAuthenticated = (status_sumary == EXECUTION_LOGIN_CODE_SUCCESS) ? true : false;
                break;

            case COMMAND_ENTER_LIBRARY:
                status_sumary = proceed_enter_library();
                break;

            case COMMAND_GET_BOOKS:
                status_sumary = proceed_get_books();
                break;

            case COMMAND_GET_BOOK:
                status_sumary = proceed_get_book();
                break;

            case COMMAND_ADD_BOOK:
                status_sumary = proceed_add_book();
                break;

            case COMMAND_DELETE_BOOK:
                status_sumary = proceed_delete_book();
                break;

            case COMMAND_LOGOUT:
                status_sumary = proceed_logut();
                break;

            case COMMAND_INVALID:
                cout << MESSAGE_COMMAND_INVALID << endl;
                break;

        }
        CHECK(status_sumary < 0, MESSAGE_COMMAND_FAILED);

    } FOREVER;


    return 0;
}

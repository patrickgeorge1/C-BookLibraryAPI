#include <iostream>
#include <string>
#include "Utils/utils.h"
#include "Utils/api.h"
#include <stdlib.h>



using namespace std;

int main() {

    bool isAuthenticated = false;
    string command;
    string token("-");
    string access_library_token("-");
    int status_sumary;

    // get host
    string host = getIPbyHostName();


    do {
        // get command
        cin >> command;
        switch (getSwitchCommand(command)) {
            // CHECK AND PERFORM EACH COMMAND

            case COMMAND_EXIT:
                exit(EXIT_SUCCESS);
                break;

            case COMMAND_REGISTER:
                status_sumary = proceed_register(host);
                break;

            case COMMAND_LOGIN:
                // log in and save cookie in token
                status_sumary = proceed_login(host, token);
                isAuthenticated = (status_sumary == 1) ? true : false;
                if (isAuthenticated) {
                    cout << " Authentication successful !" << endl;
                }
                break;

            case COMMAND_ENTER_LIBRARY:
                // save token in access_library_token
                status_sumary = 1;
                if (token == "-") cout << "You have to    log in/ get access     first" << endl;
                else status_sumary = proceed_enter_library(token, host, access_library_token);
                if (access_library_token != "-") {
                    access_library_token = "Authorization: Bearer " + access_library_token;
                    cout << "Accessed successfully ! " << endl;
                }
                break;

            case COMMAND_GET_BOOKS:

                if (access_library_token != "-") status_sumary = proceed_get_books(host, token, access_library_token);
                else cout << "You have to    log in/ get access     first" << endl;
                break;

            case COMMAND_GET_BOOK:
                if (access_library_token != "-") status_sumary = proceed_get_book(host, token, access_library_token);
                else cout << "You have to    log in/ get access     first" << endl;
                break;

            case COMMAND_ADD_BOOK:
                if (access_library_token != "-") status_sumary = proceed_add_book(host, token, access_library_token);
                else cout << "You have to    log in/ get access     first" << endl;
                break;

            case COMMAND_DELETE_BOOK:
                if (access_library_token != "-") status_sumary = proceed_delete_book(host, token, access_library_token);
                else cout << "You have to    log in/ get access     first" << endl;

                break;

            case COMMAND_LOGOUT:
                // log out and delete token and cookie
                if (token != "-") {
                    status_sumary = proceed_logut(host, token, access_library_token);
                }
                else cout << "You have to    log in/ get access     first" << endl;
                token = "-";
                access_library_token = "-";
                break;

            case COMMAND_INVALID:
                cout << MESSAGE_COMMAND_INVALID << endl;
                break;
        }

        // check if any request failed
        CHECK(status_sumary < 0, MESSAGE_COMMAND_FAILED);
        cout << endl << endl << "-------------------------------" << endl << endl << endl << endl;
    } FOREVER;


    return 0;
}

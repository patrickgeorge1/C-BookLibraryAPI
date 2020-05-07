#include <iostream>
#include <string>
#include <sys/socket.h>
#include "Utils/utils.h"
#include "Utils/api.h"
#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>


using namespace std;

int main() {

    bool isAuthenticated = false;
    string command;
    string token("-");
    string access_library_token("-");
    int status_sumary;

    string host = getIPbyHostName();


    do {
        cin >> command;
        switch (getSwitchCommand(command)) {
            case COMMAND_EXIT:
                exit(EXIT_SUCCESS);
                break;

            case COMMAND_REGISTER:
                status_sumary = proceed_register(host);
                break;

            case COMMAND_LOGIN:
                status_sumary = proceed_login(host, token);
                isAuthenticated = (status_sumary == 1) ? true : false;
                if (isAuthenticated) {
                    cout << " Authentication successful !" << endl;
                }
                break;

            case COMMAND_ENTER_LIBRARY:
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
                if (token != "-") {
                    status_sumary = proceed_logut(host, token, access_library_token);
                    cout << "Logged out " << endl;
                }
                else cout << "You have to    log in/ get access     first" << endl;
                token = "-";
                access_library_token = "-";
                break;

            case COMMAND_INVALID:
                cout << MESSAGE_COMMAND_INVALID << endl;
                break;

        }
        CHECK(status_sumary < 0, MESSAGE_COMMAND_FAILED);

    } FOREVER;


    return 0;
}

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
    string token(" ");
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
                    cout << "token = |" << token << "|" << endl;
                }
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

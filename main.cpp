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
//    int http_tcp_socket = open_connection(host, 8080, AF_INET, SOCK_STREAM, 0);
//    char * message = compute_post_request(host,  ROUTE_REGISTER, REQUEST_FORMAT_URL_ENCODED, body_data, 3, NULL, 0);
//    send_to_server(http_tcp_socket, message);
//    char* response = receive_from_server(http_tcp_socket);
//    printf("%s\n", response);
//    close_connection(http_tcp_socket);


    char **body_data = (char **) malloc(3 * sizeof(char *));
    body_data[0] = (char *)"a=g";
    body_data[1] = (char *)"p=p";
    body_data[2] = (char *)"t=q";

//    int sockfd = open_connection(host, WEBSITE_PORT, AF_INET, SOCK_STREAM, 0);
//    char *message = compute_post_request(host,  "/api/v1/dummy", "application/x-www-form-urlencoded", body_data, 3, NULL, 0);
//    printf("message %s \n", message);
//    send_to_server(sockfd, message);
//    char *response = receive_from_server(sockfd);
//    printf("%s\n", response);
//    close_connection(sockfd);


//    int sockfd = open_connection("3.8.116.10", 8080, AF_INET, SOCK_STREAM, 0);
//    char *message = compute_get_request("3.8.116.10", " /api/v1/dummy", NULL, NULL, 0);
//    send_to_server(sockfd, message);
//    printf("response %s \n", message);
//    char * response = receive_from_server(sockfd);
//    printf("%s\n", response);
//    close_connection(sockfd);


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
                    cout << "token is |" << token << "|" << endl;
                } else cout << "auth failed" << endl;
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

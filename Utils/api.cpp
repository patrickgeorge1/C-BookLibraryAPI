//
// Created by patrickgeorge1 on 5/5/20.
//

#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstring>
#include "api.h"
#include "utils.h"

using namespace std;

string getIPbyHostName() {
    struct hostent *hp = gethostbyname(WEBSITE_HOSTNAME);
    char * host = (char *) malloc(20 * sizeof(char));
    sprintf(host, "%s ", inet_ntoa( *( struct in_addr*)( hp -> h_addr_list[0])));
    string h(host);
    free(host);
    return h;
}


int proceed_register(string host) {
    string username, password;

    cout << "username=";           cin >> username;          cout << endl;
    cout << "password=";           cin >> password;          cout << endl;

    char **body_data = (char **) malloc(2 * sizeof(char *));
    body_data[0] = (char *) malloc(40 * sizeof(char));
    strcpy(body_data[0], "username=");
    strcat(body_data[0], username.c_str());
    body_data[1] = (char *) malloc(40 * sizeof(char));
    strcpy(body_data[1], "password=");
    strcat(body_data[1], password.c_str());

    int sockfd = open_connection(host.c_str(), WEBSITE_PORT, AF_INET, SOCK_STREAM, 0);
    char *message = compute_post_request(host.c_str(),  ROUTE_REGISTER, "application/x-www-form-urlencoded", body_data, 2, NULL, 0);
    send_to_server(sockfd, message);
    string r = receive_from_server(sockfd);
    close_connection(sockfd);

    free(body_data[0]);
    free(body_data[1]);

    char * response =  (char *) malloc(r.length()  * sizeof(char));
    response = (char *) r.c_str();
    char * copy_response = (char *) malloc( sizeof(response) * sizeof(char));
    strcpy(copy_response, response);

    char * first_line = (char *) strtok(response, "\n");
    char * first_word = (char *) strtok(response, " ");
    char * status = (char *) strtok(NULL, " ");

    if (strncmp(status, "201", 3) == 0) cout << "succesfully registered !" << endl;
    else cout << "failed !" << endl;

    return (strncmp(status, "201", 3) == 0);
    return 0;
}

int proceed_login(string host, string &token) {
    string username, password;

    cout << "username=";           cin >> username;          cout << endl;
    cout << "password=";           cin >> password;          cout << endl;

    char **body_data = (char **) malloc(2 * sizeof(char *));
    body_data[0] = (char *) malloc(40 * sizeof(char));
    strcpy(body_data[0], "username=");
    strcat(body_data[0], username.c_str());
    body_data[1] = (char *) malloc(40 * sizeof(char));
    strcpy(body_data[1], "password=");
    strcat(body_data[1], password.c_str());

    int sockfd = open_connection(host.c_str(), WEBSITE_PORT, AF_INET, SOCK_STREAM, 0);
    char *message = compute_post_request(host.c_str(),  ROUTE_LOGIN, "application/x-www-form-urlencoded", body_data, 2, NULL, 0);
    send_to_server(sockfd, message);
    string r = receive_from_server(sockfd);
    close_connection(sockfd);

    free(body_data[0]);
    free(body_data[1]);

    char * response =  (char *) malloc(r.length()  * sizeof(char));
    response = (char *) r.c_str();
    char * copy_response = (char *) malloc( sizeof(response) * sizeof(char));
    strcpy(copy_response, response);

    char * first_line = (char *) strtok(response, "\n");
    char * first_word = (char *) strtok(response, " ");
    char * status = (char *) strtok(NULL, " ");


    free(response);

    if (strncmp(status, "200", 3) == 0) {
        std::string all_response (copy_response);
        std::string delimiter = "connect.sid=";

        token = all_response.substr(all_response.find(delimiter) + delimiter.length());

        delimiter = "; Path=/";
        token = token.substr(0, token.find(delimiter));
    }

    free(copy_response);
    return (strncmp(status, "200", 3) == 0);
}

int proceed_enter_library() {
    // TODO enter library

    return 1;
}

int proceed_get_books() {
    // TODO get books

    return 1;
}

int proceed_get_book() {
    string id;
    cout << "id=";      cin >> id;         cout << endl;

    // TODO get book

    return 1;
}

int proceed_add_book() {
    string title, author, genre, publisher, page_count;
    cout << "title=";              cin >> title;              cout << endl;
    cout << "author=";             cin >> author;             cout << endl;
    cout << "genre=";              cin >> genre;              cout << endl;
    cout << "publisher=";          cin >> publisher;          cout << endl;
    cout << "page_count=";         cin >> page_count;         cout << endl;

    // TODO add book

    return 1;
}

int proceed_delete_book() {
    string id;
    cout << "id=";      cin >> id;         cout << endl;

    // TODO delete book

    return 1;
}

int proceed_logut() {
    // TODO logout

    return 1;
}
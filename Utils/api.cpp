//
// Created by patrickgeorge1 on 5/5/20.
//

#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstring>
#include "api.h"
#include "utils.h"
#include "nlohmann/json.hpp"


using namespace std;
using json = nlohmann::json;

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

    json j = {
            {"username", username},
            {"password", password},
    };

    int sockfd = open_connection(host.c_str(), WEBSITE_PORT, AF_INET, SOCK_STREAM, 0);
    char *message = compute_post_request("ec2-3-8-116-10.eu-west-2.compute.amazonaws.com:8080",  ROUTE_REGISTER, "application/json", j.dump(), 2, NULL, 0);
    send_to_server(sockfd, message);
    string r = receive_from_server(sockfd);
    close_connection(sockfd);

    if (r.substr(9, 3) == "201") {
        cout << "Account crated !" << endl;
        return 1;
    }
    int posStart = r.find("{\"error\":");
    string errorPart = r.substr(posStart, 200);
    cout << errorPart << endl;

    return 0;
}

int proceed_login(string host, string &token) {
    string username, password;

    cout << "username=";           cin >> username;          cout << endl;
    cout << "password=";           cin >> password;          cout << endl;

    json j = {
            {"username", username},
            {"password", password},
    };

    int sockfd = open_connection(host.c_str(), WEBSITE_PORT, AF_INET, SOCK_STREAM, 0);
    char *message = compute_post_request("ec2-3-8-116-10.eu-west-2.compute.amazonaws.com:8080",  ROUTE_LOGIN, "application/json", j.dump(), 2, NULL, 0);
    send_to_server(sockfd, message);
    string r = receive_from_server(sockfd);
    close_connection(sockfd);

    if (r.substr(9, 3) == "200") {
        int posStart = r.find("Cookie: ");

        string cookiePart = r.substr(posStart, 200);
        int posEnd = cookiePart.find("; Path=/");

        token =  cookiePart.substr(0, posEnd);
        return 1;
    }
    int posStart = r.find("{\"error\":");
    string errorPart = r.substr(posStart, 200);
    cout << errorPart << endl;

    return 0;
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
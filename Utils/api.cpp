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

int proceed_enter_library(string token, string host, string & token_access_library) {
    string cookies[2];
    cookies[0] = token;

    int sockfd = open_connection(host.c_str(), WEBSITE_PORT, AF_INET, SOCK_STREAM, 0);
    char *message = compute_get_request("ec2-3-8-116-10.eu-west-2.compute.amazonaws.com:8080", ROUTE_ENTER_LIBRARY, NULL, cookies, 1);
    send_to_server(sockfd, message);
    string r = receive_from_server(sockfd);
    close_connection(sockfd);

    if (r.substr(9, 3) == "200") {
        int posStart = r.find("{\"token\":");
        string token_library_part = r.substr(posStart + 10, 300);
        int posEnd = token_library_part.find("\"}");
        token_access_library = token_library_part.substr(0, posEnd);
        return 1;
    }

    int posStart = r.find("{\"error\":");
    string errorPart = r.substr(posStart, 200);
    cout << errorPart << endl;
    return 0;
}

int proceed_get_books(string host, string token, string access_library_token) {
    string cookies[2];
    cookies[0] = token;
    cookies[1] = access_library_token;

    int sockfd = open_connection(host.c_str(), WEBSITE_PORT, AF_INET, SOCK_STREAM, 0);
    char *message = compute_get_request("ec2-3-8-116-10.eu-west-2.compute.amazonaws.com:8080", ROUTE_GET_BOOKS, NULL, cookies, 2);
    send_to_server(sockfd, message);
    string r = receive_from_server(sockfd);
    close_connection(sockfd);

    string delimeter = "Connection: keep-alive";
    int posStart = r.find(delimeter);
    string result = r.substr(posStart + delimeter.length() + 4, r.length());


    json j = json::parse(result);
    for (int i = 0; i < j.size(); ++i) {
        cout << j[i].at("id") << " - " << j[i].at("title") << endl;
    }
    return 1;
}

int proceed_get_book(string host, string token, string access_library_token) {
    string cookies[2];
    string web_route (ROUTE_GET_BOOK);
    cookies[0] = token;
    cookies[1] = access_library_token;

    string id;
    cout << "id=";      cin >> id;         cout << endl;
    web_route += "/" + id;

    int sockfd = open_connection(host.c_str(), WEBSITE_PORT, AF_INET, SOCK_STREAM, 0);
    char *message = compute_get_request("ec2-3-8-116-10.eu-west-2.compute.amazonaws.com:8080", web_route.c_str(), NULL, cookies, 2);
    send_to_server(sockfd, message);
    string r = receive_from_server(sockfd);
    close_connection(sockfd);

    string delimeter = "Connection: keep-alive";
    int posStart = r.find(delimeter);
    string result = r.substr(posStart + delimeter.length() + 4, r.length());

    if (r.substr(9, 3) == "200") {
        json j = json::parse(result);
        cout << "Title               -> " << j[0]["title"] << endl;
        cout << "Author              -> " << j[0]["author"] << endl;
        cout << "Publisher           -> " << j[0]["publisher"] << endl;
        cout << "Genre               -> " << j[0]["genre"] << endl;
        cout << "Number of pages     -> " << j[0]["page_count"] << endl;
        return 1;
    }
    cout << "Book not found" << endl;
    return 0;
}

int proceed_add_book(std::string host, std::string token, std::string access_library_token) {
    string cookies[2];
    cookies[0] = token;
    cookies[1] = access_library_token;

    string title, author, genre, publisher, page_count;
    getline(cin, title);
    cout << "title=";              getline(cin, title);              cout << endl;
    cout << "author=";             getline(cin, author);             cout << endl;
    cout << "genre=";              getline(cin, genre);              cout << endl;
    cout << "publisher=";          getline(cin, publisher);          cout << endl;
    cout << "page_count=";         cin >> page_count;         cout << endl;

    json j = {
            {"title", title},
            {"author", author},
            {"genre", genre},
            {"page_count", page_count},
            {"publisher", publisher}
    };
    int sockfd = open_connection(host.c_str(), WEBSITE_PORT, AF_INET, SOCK_STREAM, 0);
    char *message = compute_post_request("ec2-3-8-116-10.eu-west-2.compute.amazonaws.com:8080",  ROUTE_ADD_BOOK, "application/json", j.dump(), 2, cookies, 2);
    send_to_server(sockfd, message);
    string r = receive_from_server(sockfd);
    close_connection(sockfd);


    if (r.substr(9, 3) == "200") {
        cout << "book added" << endl;
        return 1;
    }

    cout << "Book cannot be added, check again the filds" << endl;
    return 0;
}

int proceed_delete_book(std::string host, std::string token, std::string access_library_token) {
    string cookies[2];
    cookies[0] = token;
    cookies[1] = access_library_token;

    string id;
    cout << "id=";      cin >> id;         cout << endl;

    string web_route (ROUTE_REMOVE_BOOK);
    web_route += id;

    int sockfd = open_connection(host.c_str(), WEBSITE_PORT, AF_INET, SOCK_STREAM, 0);
    char *message = compute_delete_request("ec2-3-8-116-10.eu-west-2.compute.amazonaws.com:8080", web_route.c_str(), NULL, cookies, 2);
    send_to_server(sockfd, message);
    string r = receive_from_server(sockfd);
    close_connection(sockfd);

    if (r.substr(9, 3) == "200") {
        cout << "book deleted" << endl;
        return 1;
    }
    cout << "cannot delete book, check again the id " << endl;
    return 0;
}

int proceed_logut(std::string host, std::string token, std::string access_library_token) {
    // TODO logout

    return 1;
}
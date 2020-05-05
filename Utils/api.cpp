//
// Created by patrickgeorge1 on 5/5/20.
//

#include <iostream>
#include "api.h"

using namespace std;

int proceed_register() {
    string username, password;

    cout << "username=";           cin >> username;          cout << endl;
    cout << "password=";           cin >> password;          cout << endl;

    //TODO register

    return 1;
}

int proceed_login() {
    string username, password;

    cout << "username=";           cin >> username;          cout << endl;
    cout << "password=";           cin >> password;          cout << endl;

    // TODO login

    return 1;
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
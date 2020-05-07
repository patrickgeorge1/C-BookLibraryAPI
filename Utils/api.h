//
// Created by patrickgeorge1 on 5/5/20.
//

#ifndef BOOKLIBRARY_API_H
#define BOOKLIBRARY_API_H



std::string getIPbyHostName();
int proceed_register(std::string);
int proceed_login(std::string, std::string &);
int proceed_enter_library(std::string, std::string, std::string &);
int proceed_get_books(std::string, std::string, std::string);
int proceed_get_book(std::string, std::string, std::string);
int proceed_add_book(std::string, std::string, std::string);
int proceed_delete_book(std::string, std::string, std::string);
int proceed_logut(std::string, std::string, std::string);

#endif //BOOKLIBRARY_API_H

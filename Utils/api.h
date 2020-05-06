//
// Created by patrickgeorge1 on 5/5/20.
//

#ifndef BOOKLIBRARY_API_H
#define BOOKLIBRARY_API_H



std::string getIPbyHostName();
int proceed_register(std::string);
int proceed_login(std::string, std::string &);
int proceed_enter_library();
int proceed_get_books();
int proceed_get_book();
int proceed_add_book();
int proceed_delete_book();
int proceed_logut();

#endif //BOOKLIBRARY_API_H

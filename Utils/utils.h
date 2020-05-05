//
// Created by patrickgeorge1 on 5/5/20.
//

#ifndef BOOKLIBRARY_UTILS_H
#define BOOKLIBRARY_UTILS_H

#define FOREVER while(1)

#define WEBSITE_HOSTNAME ec2-3-8-116-10.eu-west-2.compute.amazonaws.com
#define WEBSITE_PORT 8080
#define COMMAND_INVALID -1
#define COMMAND_EXIT 0
#define COMMAND_REGISTER 1
#define COMMAND_LOGIN 2
#define COMMAND_ENTER_LIBRARY 3
#define COMMAND_GET_BOOKS 4
#define COMMAND_GET_BOOK 5
#define COMMAND_ADD_BOOK 6
#define COMMAND_DELETE_BOOK 7
#define COMMAND_LOGOUT 8

#define MESSAGE_COMMAND_INVALID "camanda introdusa nu este valida"
#define MESSAGE_COMMAND_FAILED "nu s-a putut executa comanda"

#define EXECUTION_LOGIN_CODE_SUCCESS 1
#define EXECUTION_LOGIN_CODE_FAIL 2

void CHECK(bool ok, std::string message);
void DIE(bool ok, std::string message);
int getSwitchCommand(std::string command);
void send_to_server(int sockfd, char *message);
char *receive_from_server(int sockfd);
int open_connection(const char *host_ip, int portno, int ip_type, int socket_type, int flag);
void close_connection(int sockfd);
char *compute_get_request(const char *host, const char *url, char *query_params,
                          char **cookies, int cookies_count);
char *compute_post_request(const char *host, const char *url, char* content_type, char **body_data,
                           int body_data_fields_count, char **cookies, int cookies_count);
#endif //BOOKLIBRARY_UTILS_H

//
// Created by patrickgeorge1 on 5/5/20.
//


#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "utils.h"
#include "buffer.h"
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <stdio.h>
#include <string.h>     /* memcpy, memset */

using namespace std;


void CHECK(bool ok, std::string message) {
    // defensive programming
    if (ok) {
        std::cout << message << std::endl;
    }
}

void DIE(bool ok, std::string message) {
    // defensive programming
    if (ok) {
        std::cout << message << std::endl;
        exit(EXIT_FAILURE);
    }
}

int getSwitchCommand(std::string command) {
    if (command == "exit") return COMMAND_EXIT;
    else
        if (command == "register") return COMMAND_REGISTER;
        else
            if (command == "login") return COMMAND_LOGIN;
            else
                if (command == "enter_library") return COMMAND_ENTER_LIBRARY;
                else
                    if (command == "get_books") return COMMAND_GET_BOOKS;
                    else
                        if (command == "get_book") return COMMAND_GET_BOOK;
                        else
                            if (command == "add_book") return COMMAND_ADD_BOOK;
                            else
                                if (command == "delete_book") return COMMAND_DELETE_BOOK;
                                else
                                    if (command == "logut") return COMMAND_LOGOUT;
                                    else return COMMAND_INVALID;
}

int open_connection(const char *host_ip, int portno, int ip_type, int socket_type, int flag)
{
    struct sockaddr_in serv_addr;
    int sockfd = socket(ip_type, socket_type, flag);
    DIE(sockfd < 0, "ERROR opening socket");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = ip_type;
    serv_addr.sin_port = htons(portno);
    inet_aton(host_ip, &serv_addr.sin_addr);

    /* connect the socket */
    DIE(connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0, "ERROR connecting");

    return sockfd;
}

void send_to_server(int sockfd, char *message)
{
    int bytes, sent = 0;
    int total = strlen(message);

    do
    {
        bytes = write(sockfd, message + sent, total - sent);
        DIE(bytes < 0, "ERROR writing message to socket");


        if (bytes == 0) {
            break;
        }

        sent += bytes;
    } while (sent < total);
}

// TODO PROBLEM SOLVED
std::string receive_from_server(int sockfd)
{
    char response[BUFLEN];
    buffer buffer = buffer_init();

    int header_end = 0;
    int content_length = 0;

    do {
        int bytes = read(sockfd, response, BUFLEN);
        DIE(bytes < 0, "ERROR reading response from socket");

        if (bytes == 0) {
            break;
        }

        buffer_add(&buffer, response, (size_t) bytes);
        header_end = buffer_find(&buffer, HEADER_TERMINATOR, HEADER_TERMINATOR_SIZE);

        if (header_end >= 0) {
            header_end += HEADER_TERMINATOR_SIZE;

            int content_length_start = buffer_find_insensitive(&buffer, CONTENT_LENGTH, CONTENT_LENGTH_SIZE);

            if (content_length_start < 0) {
                continue;
            }

            content_length_start += CONTENT_LENGTH_SIZE;
            content_length = strtol(buffer.data + content_length_start, NULL, 10);
            break;
        }

    } while (1);
    size_t total = content_length + (size_t) header_end;

    while (buffer.size < total) {
        int bytes = read(sockfd, response, BUFLEN);

        DIE(bytes < 0, "ERROR reading response from socket");

        if (bytes == 0) {
            break;
        }
        buffer_add(&buffer, response, (size_t) bytes);

    }

    buffer_add(&buffer, "", 1);
    std::string result(buffer.data);
    buffer_destroy(& buffer);
    return result;

//    int bytes = read(sockfd, response, BUFLEN);
//    DIE(bytes < 0, "ERROR reading response from socket");
//    std::string res (response);
//    return  res;
}

void close_connection(int sockfd)
{
    close(sockfd);
}


void compute_message(char *message, const char *line)
{
    strcat(message, line);
    strcat(message, "\r\n");
}

char *compute_get_request(const char *host, const char *url, char *query_params,
                          string cookies[MAX_COOKIES], int cookies_count)
{
    char *message = (char *) calloc(BUFLEN, sizeof(char));
    char *line = (char *) calloc(LINELEN, sizeof(char));

    // Step 1: write the method name, URL, request params (if any) and protocol type
    if (query_params != NULL) {
        sprintf(line, "GET %s?%s HTTP/1.1", url, query_params);
    } else {
        sprintf(line, "GET %s HTTP/1.1", url);
    }
    compute_message(message, line);

    // Step 2: add the host
    line = (char *) calloc(LINELEN, sizeof(char));
    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    // Step 3 (optional): add headers and/or cookies, according to the protocol format
    if (cookies_count >  0) {
        for (int i = 0; i < cookies_count; ++i) {
            compute_message(message, cookies[i].c_str());
        }
    }
    // Step 4: add final new line
    compute_message(message, "");
    return message;
}

char *compute_post_request(const char *host, const char *url, const char* content_type, std::string body_data,
                           int body_data_fields_count, string cookies[MAX_COOKIES], int cookies_count)
{
    char *message = (char *) calloc(BUFLEN, sizeof(char));
    char *line = (char *) calloc(LINELEN, sizeof(char));
    char *body_data_buffer =  (char *) calloc(LINELEN, sizeof(char));

    // Step 1: write the method name, URL and protocol type
    sprintf(line, "POST %s HTTP/1.1", url);
    compute_message(message, line);

    // Step 2: add the host
    line = (char *) calloc(LINELEN, sizeof(char));
    sprintf(line, "Host: %s", host);
    compute_message(message, line);
    /* Step 3: add necessary headers (Content-Type and Content-Length are mandatory)
            in order to write Content-Length you must first compute the message size
    */
    line = (char *) calloc(LINELEN, sizeof(char));
    sprintf(line, "Content-Type: %s", content_type);
    compute_message(message, line);

//    strcat(body_data_buffer, body_data[0]);
//    for (int i = 1; i < body_data_fields_count; ++i) {
//        strcat(body_data_buffer, "&");
//        strcat(body_data_buffer, body_data[i]);
//    }

    line = (char *) calloc(LINELEN, sizeof(char));
    sprintf(line, "Content-Length: %zu", body_data.length());
    compute_message(message, line);

    // Step 4 (optional): add cookies
    if (cookies_count >  0) {
        for (int i = 0; i < cookies_count; ++i) {
            compute_message(message, cookies[i].c_str());
        }
    }
    // Step 5: add new line at end of header
    compute_message(message, "");


    // Step 6: add the actual payload data
    memset(line, 0, LINELEN);
    if (body_data_fields_count > 0)
    compute_message(message, body_data.c_str());

    free(line);
    return message;
}

char *compute_delete_request(const char *host, const char *url, char *query_params,
                          string cookies[MAX_COOKIES], int cookies_count)
{
    char *message = (char *) calloc(BUFLEN, sizeof(char));
    char *line = (char *) calloc(LINELEN, sizeof(char));

    // Step 1: write the method name, URL, request params (if any) and protocol type
    if (query_params != NULL) {
        sprintf(line, "DELETE %s?%s HTTP/1.1", url, query_params);
    } else {
        sprintf(line, "DELETE %s HTTP/1.1", url);
    }
    compute_message(message, line);

    // Step 2: add the host
    line = (char *) calloc(LINELEN, sizeof(char));
    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    // Step 3 (optional): add headers and/or cookies, according to the protocol format
    if (cookies_count >  0) {
        for (int i = 0; i < cookies_count; ++i) {
            compute_message(message, cookies[i].c_str());
        }
    }
    // Step 4: add final new line
    compute_message(message, "");
    return message;
}
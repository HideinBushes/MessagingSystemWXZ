#ifndef PACKAGE_HPP_
#define PACKAGE_HPP_


#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <thread>
#include <vector>
#include <string>
#include <mutex>
#include <map>
#include <fstream>

#define bufsize 1024
using namespace std;

//Server member function
class Server{
private:
    int listenfd, connfd;
    int portNum;
    struct sockaddr_in server_addr, client_addr;
    socklen_t size;
public:
    Server(int portNum);//constructor
    void server_addr_init();//struct server_addr
    void bind_listen(); //bind() & listen()
    int accept_client(); //listen()
};

void recieve_client_list(int sockfd);
void send_client_list(int sockfd);
void str_read(int sockfd); // string read
void str_write(int sockfd); // string write


#endif
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
//Client member function
using namespace std;

void header();
void line();

class Client {
private:
    int sockfd;
    int portNum;
    //string username; 
    struct sockaddr_in server_addr;
    const char* IP;
public:
    Client(int portNum, const char* IP);
    void clientinit();
    void clientconn();
    int get_sockfd();
    //static void str_cli();
    void clientclose();
    static void str_send(int sockfd);
    static void str_recieve(int sockfd);
    void login_info(string username);

};


#endif
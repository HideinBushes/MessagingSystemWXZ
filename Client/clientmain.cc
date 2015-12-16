#include "package.hpp"

string myname;


int main(){
    header();
	cin>>myname;
	line();
    int sockfd ;
      //username there is a map in server, map[string username, int sockfd
    Client c1(1510, "155.246.84.58");
    c1.clientinit();
    c1.clientconn();
    sockfd = c1.get_sockfd();

    c1.login_info(myname);  

    thread t1_send(Client::str_send, sockfd);
    thread t1_recieve(Client::str_recieve, sockfd);

    t1_send.join();
    t1_recieve.join();
}

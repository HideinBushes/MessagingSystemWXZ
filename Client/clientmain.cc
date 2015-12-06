#include "package.hpp"



int main(){
	cout<< "\n-->Messaging System \n";
	cout<<"-->Login...\n";
	cout<<"-->Username: ";
	string username;
	cin>>username;
    int sockfd ;
      //username there is a map in server, map[string username, int sockfd
    Client c1(1510, "127.0.0.1");
    c1.clientinit();
    c1.clientconn();
    sockfd = c1.get_sockfd();
    c1.login_info(username);
    
    thread t1_send(Client::str_send, sockfd);
    thread t1_recieve(Client::str_recieve, sockfd);

    t1_send.join();
    t1_recieve.join();
}

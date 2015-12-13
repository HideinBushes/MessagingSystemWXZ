#include "package.hpp"

int main() {
    
    vector<int> connfd; //one connfd for each client
    vector<thread> t_read; //one read thread for each client
    vector<thread> t_write; //one write thread for each client
    int i=0; //
    
    Server s1(1510); // read port
    s1.server_addr_init();
    s1.bind_listen();
    
    while(1) {
        connfd.push_back(s1.accept_client());
        cout << "connfd[" << i << "] = " << connfd.back() << endl;
        //init imformation
        recieve_client_list(connfd.back());
        send_client_list(connfd.back());
        //thread
        t_read.push_back(thread(str_read, connfd.back()));
        t_write.push_back(thread(str_write, connfd.back()));
        i++;
    }

    
}
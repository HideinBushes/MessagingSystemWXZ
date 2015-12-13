#include "package.hpp"

vector<string> queue;
map<string,int> client_list;
mutex rw;


Server::Server(int portNum):portNum(portNum){
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        cout << "\nError establishing socket..." << endl;
        exit(1);
    }
    cout << "\nSocket server has been created..." << endl;
}

void Server::server_addr_init(){
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);
    server_addr.sin_addr.s_addr = htons (INADDR_ANY);
}

void Server::bind_listen(){
    if ( bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        cout << "\nError binding connection, the socket has already been established..." << endl;
        exit(1);
    }
    cout << "ready to listen" << endl;
    listen(listenfd, 5);
}

int Server::accept_client(){
    size = sizeof(client_addr);
    connfd = accept(listenfd, (struct sockaddr*)&client_addr, &size);
    if(connfd < 0) {
        cout << "\nError on accepting client..." << endl;
    }
    cout << "Client connected! Port Number: " << portNum << endl;
    return connfd;
}







//1.read name from client
//2.push back to client list
//3.show current clients(name and connfd)

void recieve_client_list(int sockfd) {
    char buffer[bufsize];
    read(sockfd, buffer, bufsize);
    string name(buffer);
    client_list[name] = sockfd;
    for (map<string,int>::iterator itr = client_list.begin(); itr != client_list.end(); ++itr) {
        cout << "\nname: " << itr->first << endl;
        cout << "connfd :" << itr->second << endl;
    }
}

//1.send all clients' info to certain client as: (*)(connfd)(name)
void send_client_list(int sockfd) {
    char buffer[bufsize];
    for (map<string,int>::iterator itr = client_list.begin(); itr != client_list.end(); ++itr) {
        string info = '*' + to_string(itr->second) + itr->first;
        strcpy(buffer, info.c_str());
        write(sockfd, buffer, bufsize);
        cout << "[send_client_list] info is sent: " << itr->first << " " << itr->second << endl;
    }
}

//1.read from client
//2.output queue
//3.if buffer[1] == #, delete this client in client_list, and end thread.
//4.if buffer[1] == @, insert queue for all clients that are exist.
void str_read(int sockfd) {
    while(1){
        char buffer[bufsize];
        read(sockfd, buffer, bufsize);
        string read;

        //1.delete client in client_list
        //2.end thread
        if (buffer[1] == '#') {
            read = to_string(sockfd) + buffer;
            queue.push_back(read);
            cout << "[str_read] recieve # Shutting Down read thread for this client!" << endl;
            for (map<string,int>::iterator itr = client_list.begin(); itr != client_list.end(); ++itr) {
                if (itr->second == sockfd) {
                    client_list.erase(itr);
                }
            }
            return;
        }
        
        //without token ! & #
        
        rw.lock();
        if(buffer[0] != '0') {
            read = to_string(sockfd) + buffer;
            cout << "[str_read] read from client:" << read << endl;
            queue.push_back(read);
            for(int i=0; i<queue.size(); i++) {
                cout << "[str_read] queue[" << i << "]:" << queue[i] << endl;
            }
        }

        else {
            for (map<string, int>::iterator itr = client_list.begin(); itr != client_list.end(); ++itr) {
                buffer[0]= itr->second+'0';
                read = to_string(sockfd) + buffer;
                queue.push_back(read);
            }
            
        }
        rw.unlock();
        
        
        
    }
}

//1. read from queue
//2. write to client
//3. erase queue[0]
//4. if buffer[1] == #, end thread
//5. if buffer[1] == !, send client info
void str_write(int sockfd) {
    while(1)
    {
        rw.lock();
        if(!queue.empty())
        {
            char buffer[bufsize];
            strcpy(buffer, queue[0].c_str());
            //
            if((int)(buffer[1]-'0') == sockfd) {
                cout << "\n[str_write]: detected connfd: " << sockfd << "]" << endl;
                cout << "[str_write]: message copied from queue[0]:" << buffer << endl;
                queue.erase( queue.begin() );
                if (buffer[2] != '!') {
                    if (buffer[2] == '#') {
                        cout << "[str_write] recieve # Shutting Down write thread for this client!" << endl;
                        write(sockfd, buffer, bufsize);
                        close(sockfd);
                        rw.unlock();
                        return;
                    }
                    
                    string w;
                    for (map<string,int>::iterator itr = client_list.begin(); itr != client_list.end(); ++itr) {
                        if (itr->second == (int)(buffer[0]-'0') ) {
                            w = itr->first + ':' + ' ' + (buffer+2);
                            break;
                        }
                    }
                    strcpy(buffer, w.c_str());
                    write(sockfd, buffer, bufsize);

                }
                if (buffer[2] == '!') {
                    cout << "[str_write] recieve ! send map" << endl;
                    send_client_list(sockfd);
                }
            }
        }
        rw.unlock();
    }
}



#include "package.hpp"
using namespace std;

map <string, int> usermap;
map <string,int>::iterator it;
int h=0;

extern string myname;

Client::Client(int portNum, const char* IP): portNum(portNum),IP(IP){
    //socket()
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        cout << "  \nError establishing socket..." << endl;
        exit(1);
    }
    cout << "  => Socket client has been created..." << endl;
}

void Client::clientinit(){

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);
    inet_pton(AF_INET,IP,&server_addr.sin_addr);
}

void Client::clientconn(){
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == 0){
        cout << "  => Connection to the server port number: " << portNum << endl;
        line();
        cout<< "Users Online(type in @user to select your target, e.g. @tim): "<<endl;
    }
    else{
        cout<<"  => Error connecting to server,please restart.\n";
        close(sockfd);
        exit(1);
    }
}

int Client::get_sockfd() {
    return sockfd;
}
void Client::clientclose(){
    close(sockfd);
}

void Client::str_send(int sockfd) {
    while(1) {
        char buffer[bufsize];
        cin >> buffer;
        string name(buffer+1);

        if(buffer[0]=='@'){
            if (usermap.count(name)>0){
                it = usermap.find(name);
                h=it->second;
                line();
            }
            else{
                h=0;
                line();
            }
            continue;
        }

        if(buffer[0]=='!'){

            it =usermap.find(myname);
            h=it->second;
            line();
            cout<< "Users online(type in @user to select your target, e.g. @tim): "<<endl;
            usermap.clear();
        }

        if(buffer[0] == '#'){
            it =usermap.find(myname);
            h=it->second;
            string end(buffer);
            end = to_string(h) + end;
            strcpy(buffer, end.c_str());
            write(sockfd, buffer, bufsize);
            cout << "thread_send is closed"<<endl;
            return;
        }

        if(buffer[0]=='&'){
            string file(buffer);
            file=to_string(h)+file;
            strcpy(buffer, file.c_str());
            write(sockfd,buffer,bufsize);
           
            const char* filename=buffer+2;
            FILE *img=fopen(filename, "rb");
            fseek(img, 0, SEEK_END);
            unsigned long filesize = ftell(img);
            //send filesize
            string size=to_string(filesize);
            size=to_string(h)+size;
            strcpy(buffer, size.c_str());

            write(sockfd,buffer,bufsize);

            char* filebuffer=new char[filesize];
            rewind(img);
            fread(filebuffer, sizeof(char), filesize, img);
            fclose (img); 
            write(sockfd, filebuffer,filesize);
            cout<<"File has been upload to the server!"<<endl;
            delete [] filebuffer;
            continue;
        }

        string message(buffer);
        message = to_string(h) + message;
        strcpy(buffer, message.c_str());
        write(sockfd, buffer, bufsize);


    }   
}

void Client::str_recieve(int sockfd) {
    while(1) {
        char buffer[bufsize];
        read(sockfd, buffer, bufsize);
        int fd;
        //cout << "done reading" << endl;
        if(buffer[0]=='*' && buffer[2]!='#'){
            int fd=buffer[1]-'0';
            string name(buffer+3);
            usermap[name]=fd;
            cout<<"User: "<<name<<" ID: "<<fd<<endl;
        }

        if(buffer[0]!='*' && buffer[2]!='#'){
            cout << buffer << endl;
        }

        if(buffer[2]=='#') {
            close(sockfd);
            cout<<"thread_recieve is closed"<<endl;
            cout<<"client closed."<<endl;
            return;
        }
    }
}

void Client::login_info(string username){
    char buffer[bufsize];
    buffer[0]='@';
    strcpy(buffer+1, username.c_str());
    write(sockfd, buffer, bufsize);
}



void line(){
      for(int i=0;i<60;i++)
        cout<<'-';  
    cout<<endl;
}

void header(){
    for(int i=0;i<60;i++){
        cout<<'-';
    }
    cout<<endl;
    for(int i=0;i<23;i++)
        cout<<' ';
    cout<< "Messaging System \n";
    cout<< "< Program developed by Jiabin Xiang, Pandong Zhang and Shan Wang > \n";
    line();
    cout<<"   =>Login...\n";
    cout<<"   =>Username: ";
}



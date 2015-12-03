#include "package.hpp"
#include <thread>
#include <mutex>
#define clientnum 10
using namespace std;
char temp[clientnum][bufsize];
mutex m;

void testf(int connfd,int i){
   m.lock();
   cout<< "client"<< i <<": ";
   read(connfd, temp[i],bufsize);
   for(int j=0;j<clientnum;j++){
        if(temp[j][0]==i)
            write(connfd,temp[j],bufsize);

   }
   m.unlock();
}

int main(){
    int connfd;
    Server s1(1515);
    s1.Serverinit();
    s1.getready();


    thread t[clientnum];


    for(int i=0;i<clientnum ;i++){
        connfd=s1.waitforclient();
        t[i]=thread(testf,connfd,i);
    }
}

#include <iostream>

using namespace std;

int main()
{
   unsigned long size=100000;
   unsigned char* buffer=(unsigned char*)&size;
   cout<<buffer;
}
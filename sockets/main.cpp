#include "ListeningSocket.hpp"
#include <iostream>
#include <stdio.h>
using namespace std;

int main(){
 cout<<"Simple web socket...."<<endl;


 cout<<"Bing web server"<<endl;
 HDE::BindingSocket socket(AF_INET, SOCK_STREAM, 0, 81, INADDR_ANY);

 cout<<"Listening Socket"<<endl;
    HDE::ListeningSocket listeningSocket(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10);

    cout<<"Success "<<endl;
}
//============================================================================
// Name        : DemoServer.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Server in C++
//============================================================================

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main()
{
	int client, server;
	int portNum = 1800;
	bool isExit = false;
	int bufsize = 1024;
	char buffer[bufsize];

	struct sockaddr_in server_addr;
	socklen_t size;

	//init socket
	client = socket(AF_INET, SOCK_STREAM, 0);
	if(client < 0){
		cout << "Error establishing connecting." << endl;
		exit(1);
	}

	cout << "Server socket connecting created.." << endl;

    server_addr.sin_family = AF_INET;
//    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_addr.s_addr = inet_addr("192.168.11.93");
    server_addr.sin_port = htons(portNum);

    if(bind(client,(struct sockaddr*)&server_addr, sizeof(server_addr))<0){
    	cout << "Error bingding socket..." << endl;
    	exit(1);
    }
    size = sizeof(server_addr);
    cout << "locking for clients..." << endl;

    //listening socket

    listen(client, 1);

    //Accept client
    server = accept(client, (struct sockaddr*)&server_addr, &size);

    if(server<0){
    	cout << "Error on accepting ..." << endl;
    	exit(1);
    }

    while(server>0){
    	strcpy(buffer, "server connected...\n");
    	send(server, buffer, bufsize, 0);

    	cout << "connnected with client..." << endl;
    	cout << "Enter # to end the connection." << endl;

		cout << "Client: ";
		do{
			recv(server, buffer, bufsize, 0);
			cout << buffer << " ";
			if(*buffer == '#'){
				*buffer = '*';
				isExit = true;
			}
		}while(*buffer != '*');

		do{
			cout << "\nServer: ";
			do{
				cin >> buffer;
				send(server, buffer, bufsize, 0);
				if(*buffer == '#'){
					send(server, buffer, bufsize, 0);
					*buffer = '*';
					isExit = true;
				}
			}while(*buffer != '*');

			cout << "Client: ";
			do{
				recv(server, buffer, bufsize, 0);
				cout << buffer << " ";
				if(*buffer == '#'){
					*buffer == '*';
					isExit = true;
				}
			}while(*buffer != '*');
		}while(!isExit);

		cout << "Connection terminaler..." << endl;
		cout << "Goodbye.." << endl;
		exit(1);
    }
    close(client);
    return 0;
}

//============================================================================
// Name        : DemoClient.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <fstream>

using namespace std;

// Hàm cắt file và trả về 1 nếu là file được nhận, 0 nếu là đoạn thông điệp chat
int sub(string *a);

int main() {
	int client, server;
	int portNum = 1700;
	bool isExit = false;
	int bufsize = 1024;
	char buffer[bufsize];
	char *ip = "192.168.11.17";
	ofstream file("input.txt");


	struct sockaddr_in server_addr;

	//init socket
	client = socket(AF_INET, SOCK_STREAM, 0);
	if (client < 0) {
		cout << "Error creating socket..." << endl;
		exit(1);
	}

	cout << "Client socket created" << endl;

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portNum);
	server_addr.sin_addr.s_addr = inet_addr("192.168.11.93");

	//connecting socket server
	if (connect(client, (struct sockaddr*) &server_addr, sizeof(server_addr))
			== 0) {
		cout << "Connecting to server..." << endl;
	}

	recv(client, buffer, bufsize, 0);
	cout << "Connection confirmed" << endl;

	cout << "Enter # to end the connection." << endl;

	//communicate client - server
	do {
		cout << "Client: ";
		do {
			cin >> buffer;
			send(client, buffer, bufsize, 0);
			if (*buffer == '#') {
				send(client, buffer, bufsize, 0);
				*buffer = '*';
				isExit = true;
			}
		} while (*buffer != 42);

		cout << "Server: ";
		do {
			recv(client, buffer, bufsize, 0);
			memset(buffer, 0, sizeof(buffer));
			string buff(buffer);
			int fi = sub(&buff);
//			cout << buffer << " ";
			if(fi == 1){
				fstream f;
				f.open("input.txt", ios::in | ios::out);
				f << buff;
			}
			else cout << buff << " ";
			if (buff == "#") {
				*buffer = '*';
				isExit = true;
			}
		} while (*buffer != 42);
		cout << endl;
	} while (!isExit);

	cout << "Connection terminaler..." << endl;
	cout << "Goodbye.." << endl;

	close(client);

	return 0;
}

int sub(string *a) {
	string b = a->substr(0, 2);
	*a = a->erase(0, 2);
	if (b == "fi") {
		return 1;
	} else
		return 0;
}

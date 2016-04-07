#ifndef _VENDFIT_CLIENT_
#define _VENDFIT_CLIENT_

#include <iostream>    //cout
#include <stdio.h> //printf
#include <unistd.h>
#include <string.h>    //strlen
#include <string>  //string
#include <sys/socket.h>    //socket
#include <arpa/inet.h> //inet_addr
#include <netdb.h> //hostent

class VendFitClient{

public:
	VendFitClient(){};
	VendFitClient(std::string host, int port);
	bool conn();
	void stayConnected();
	void sendData(std::string data);
	int parseResponse(char opcode[], int opcodeLength);
private:
	std::string host;
	int port;
	std::string END;
	int socketFD;
	struct sockaddr_in server;
};

#endif
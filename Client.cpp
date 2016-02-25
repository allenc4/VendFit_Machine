#include "Client.h"

Client::Client(string serverName, int port){
	this->serverName = serverName;
	this->port = port;
}

bool Client::connect(){
	return false;
}

bool Client::disconnect(){
	return false;
}

void Client::checkin(){

}

bool Client::sendData(){
	return false;
}

void Client::parseResponse(char &opcode, int length){

}
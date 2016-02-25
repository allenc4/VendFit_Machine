#ifndef _CLIENT_
#define _CLIENT_

#include <string.h>

class Client{

public:
	Client(String serverName, int port);
	bool connect();
	bool disconnect();
	bool sendData();
	void parseResponse(char &opcode, int length);
private:
	String serverName;
	int portNumber;
	String END;
	void checkin();

};

#endif
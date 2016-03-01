#ifndef _VENDFIT_CLIENT_
#define _VENDFIT_CLIENT_

#include <string>
#include "spark_wiring_tcpclient.h"
#include "spark_wiring_interrupts.h"
#include "spark_wiring_usbserial.h"

class VendFitClient{

public:
	VendFitClient(){};
	VendFitClient(IPAddress ip, int port);
	void connect();
	void stayConnected();
	void sendData(std::string content);
	void parseResponse(char &opcode, int length);
private:
	IPAddress ip;
	int port;
	std::string END;
	TCPClient client;
};

#endif
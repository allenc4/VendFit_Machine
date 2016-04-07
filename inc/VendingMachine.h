#ifndef _VENDINGMACHINE_
#define _VENDINGMACHINE_

#include "Dispenser.h"
#include "VendFitClient.h"
#include "ItemType.h"
#include <string>

class VendingMachine{
public:
	VendingMachine(std::string id, int numberOfDispensers, int *pins);
	~VendingMachine();
	bool vend(int index);
	bool isReady();
	void stayAlive();
	void checkin();
	void registration();
	void initClient(std::string host, int port);
	bool checkResponse();
	char * getOpCode();
	int getOpCodeLength();
	int parseResponse();
	VendFitClient getClient();
	void updateDispenser(int id, int stock, ItemType type);
private:
	VendFitClient client;
	Dispenser * dispensers;
	int numberOfDispensers;
	bool ready;
	std::string id;
	bool hasResponse;
	int opcodeLength = 8;
	char * opcode;

};

#endif

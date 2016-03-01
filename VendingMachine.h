#ifndef _VENDINGMACHINE_
#define _VENDINGMACHINE_

#include "Dispenser.h"
#include "VendFitClient.h"
#include "ItemType.h"
#include <string>

class VendingMachine{
public:
	VendingMachine(std::string id, int numberOfDispensers, uint8_t *pins);
	~VendingMachine();
	bool vend(ItemType type);
	bool isReady();
	void stayAlive();
	void checkin();
	void registration();
	void initClient(IPAddress ip, int port);
private:
	VendFitClient client;
	Dispenser * dispensers;
	int numberOfDispensers;
	bool ready;
	std::string id;
};

#endif
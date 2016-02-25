#ifndef _VENDINGMACHINE_
#define _VENDINGMACHINE_

class VendingMachine{
public:
	VendingMachine();
	~VendingMachine();
	bool vend(int dispenserNumber);
	bool isReady();
private:
	Dispenser * dispensers;
	int numberOfDispensers;
	bool ready;
};

#endif
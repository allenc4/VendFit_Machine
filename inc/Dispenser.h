#ifndef _DISPENSER_
#define _DISPENSER_

#include "ItemType.h"

class Dispenser{
public:
	Dispenser(){};
	Dispenser(int pin);
	void vend();
	ItemType getType();
	void setType(ItemType type);
	void setStock(int stock);
	int getStock();
private:
	// Servo servo;
	ItemType type;
	int stock;
};


#endif
#ifndef _DISPENSER_
#define _DISPENSER_

#include "ItemType.h"

class Dispenser{
public:
	Dispenser();
	void vend();
	ItemType getType();
	void setStock(int stock);
	int getStock();
private:
	Servo servo;
	ItemType type;
	int stock;
};


#endif
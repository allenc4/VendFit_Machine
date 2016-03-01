#ifndef _DISPENSER_
#define _DISPENSER_

#include "ItemType.h"
#include "spark_wiring_servo.h"

class Dispenser{
public:
	Dispenser(){};
	Dispenser(uint8_t pin);
	void vend();
	ItemType getType();
	void setType(ItemType type);
	void setStock(int stock);
	int getStock();
private:
	Servo servo;
	ItemType type;
	int stock;
};


#endif
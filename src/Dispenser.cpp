#include "../inc/Dispenser.h"

Dispenser::Dispenser(int pin){
	// this->servo.attach(pin);
	// this->servo.write(180);
}

void Dispenser::vend(){
	// this->servo.write(0);
	// delay(1000);
	// this->servo.write(180);
}

ItemType Dispenser::getType(){
	return this->type;
}

void Dispenser::setType(ItemType type){
	this->type = type;
}

int Dispenser::getStock(){
	return this->stock;
}

void Dispenser::setStock(int stock){
	this->stock = stock;
}
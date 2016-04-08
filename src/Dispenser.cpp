#include "../inc/Dispenser.h"

Dispenser::Dispenser(int pin){
	if (gpioInitialise() < 0) {
		std::cout << "Error initializing pigpio!" << std::endl;
	}
	this->pin = pin;
	gpioServo(pin, PWM_RIGHT);
	usleep(750000);  // delay for 750 milliseconds 
	gpioServo(pin, PWM_OFF);
}

void Dispenser::vend(){
	gpioServo(this->pin, PWM_LEFT);
	usleep(750000);
	gpioServo(this->pin, PWM_RIGHT);
	usleep(750000);
	gpioServo(this->pin, PWM_OFF);
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

#include "VendingMachine.h"

VendingMachine::VendingMachine(int numberOfDispensers){
	this->dispensers = new Dispenser[numberOfDispensers];
	this->numberOfDispensers = numberOfDispensers;
}

VendingMachine::~VendingMachine(){
	delete[] this->dispensers;
}

bool VendingMachine::vend(ItemType type){
	bool vended = false;
	for(int i = 0; i < this->numberOfDispensers; i++)
	{
		if(this->dispensers[i]->getType() == type && this->dispensers[i]->getStock() > 0)
		{
			this->dispensers[i]->vend();
			vended = true;
		}
	}

	return vended;
}

bool VendingMachine::isReady(){
	return this->ready;
}
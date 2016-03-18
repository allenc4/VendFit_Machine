#include "VendingMachine.h"

VendingMachine::VendingMachine(std::string id, int numberOfDispensers, uint8_t *pins){
	this->id = id;
	this->dispensers = new Dispenser[numberOfDispensers];
	this->numberOfDispensers = numberOfDispensers;

	this->opcode = new char[this->opcodeLength];

	for(int i = 0; i < numberOfDispensers; i++)
	{
		this->dispensers[i] = Dispenser(pins[i]);
	}
}

VendingMachine::~VendingMachine(){
	delete[] this->dispensers;
}

bool VendingMachine::vend(ItemType type){
	this->ready = false;
	bool vended = false;
	for(int i = 0; i < this->numberOfDispensers; i++)
	{
		if(this->dispensers[i].getType() == type && this->dispensers[i].getStock() > 0)
		{
			this->dispensers[i].vend();
			vended = true;
		}
	}
	this->ready = true;
	return vended;
}

bool VendingMachine::isReady(){
	return this->ready;
}

void VendingMachine::stayAlive(){
	this->client.stayConnected();
}

void VendingMachine::checkin(){
	this->client.connect();
	this->client.sendData("{\"operation\": \"machine_checkin\", \"data\": {\"identifer\": \""+this->id+"\"}}");
}

void VendingMachine::initClient(IPAddress ip, int port){
	this->client = VendFitClient(ip, port);
}

void VendingMachine::registration(){
	this->client.connect();
	this->client.sendData("{\"operation\": \"machine_registration\", \"data\": {\"identifer\": \""+this->id+"\"}}");
}

bool VendingMachine::checkResponse(){
	return this->hasResponse;
}

char * VendingMachine::getOpCode(){
	return this->opcode;
}

int VendingMachine::getOpCodeLength(){
	return this->opcodeLength;
}

void VendingMachine::parseResponse(){
	this->hasResponse = this->client.parseResponse(this->opcode, this->opcodeLength);	
}

VendFitClient VendingMachine::getClient(){
	return this->client;
}
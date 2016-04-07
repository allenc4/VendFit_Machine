#include "../inc/VendingMachine.h"

VendingMachine::VendingMachine(std::string id, int numberOfDispensers, int *pins){
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

bool VendingMachine::vend(int index){
	if(index < this->numberOfDispensers && index >= 0)
	{
		this->dispensers[index].vend();
		return true;
	}else
	{
		return false;
	}
}

bool VendingMachine::isReady(){
	return this->ready;
}

void VendingMachine::stayAlive(){
	this->client.stayConnected();
}

void VendingMachine::checkin(){
	this->client.sendData("{\"operation\": \"machine_checkin\", \"data\": {\"identifier\": \""+this->id+"\"}}");
}

void VendingMachine::initClient(std::string host, int port){
	this->client = VendFitClient(host, port);
}

void VendingMachine::registration(){
	this->client.sendData("{\"operation\": \"machine_registration\", \"data\": {\"identifier\": \""+this->id+"\"}}");
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

int VendingMachine::parseResponse(){
	return this->client.parseResponse(this->opcode, this->opcodeLength);	
}

VendFitClient VendingMachine::getClient(){
	return this->client;
}

void VendingMachine::updateDispenser(int id, int stock, ItemType type){
	this->dispensers[id].setStock(stock);
	this->dispensers[id].setType(type);
}
#include "main.h"

#define NUMBER_OF_DISPENSERS 4

VendingMachine * vm;

uint8_t dispenserPins[4] = {A0, A1, A4, A5};

IPAddress ip(54,173,18,160);

std::string ID = "vendfit_machine_1";

int port = 8888;

void setup() 
{ 
	Serial.begin(9600);

  	vm = new VendingMachine(ID, NUMBER_OF_DISPENSERS, dispenserPins);

  	vm->initClient(ip, port);
  	vm->registration();
  	Serial.println("Setup complete");
  	Spark.variable("test", &port, INT);
} 


void loop() 
{ 
  	vm->stayAlive();
  	vm->checkin();
  	if(vm->checkResponse())
  	{
  		for(int i = 0; i < vm->getOpCodeLength(); i++)
  		{
  			Serial.print(vm->getOpCode()[i]);
  		}
  	}
  	Serial.println("");
  	delay(500);
}
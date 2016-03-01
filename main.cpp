#include "main.h"

#define NUMBER_OF_DISPENSERS 4

VendingMachine * vm;

uint8_t dispenserPins[4] = {A0, A1, A4, A5};

IPAddress ip(10,0,1,12);

std::string ID = "vendfit_machine_1";

int port = 8888;

void setup() 
{ 
	Serial.begin(9600);

  	vm = new VendingMachine(ID, NUMBER_OF_DISPENSERS, dispenserPins);

  	vm->initClient(ip, port);
  	Serial.println("Setup complete");
  	Spark.variable("test", &port, INT);
} 


void loop() 
{ 
	for(int i=0; i<7; i++) {
	  int res = get_socket_active_status(i);
	  if (SOCKET_STATUS_ACTIVE == res) {
	    Serial.println("SOCKET IN USE");
	  } else {
	    Serial.println("WE HAVE A SOCKET");
	  }
	}

  	vm->stayAlive();
}

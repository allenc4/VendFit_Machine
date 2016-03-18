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
} 


void loop() 
{ 
  	vm->stayAlive();
    vm->parseResponse();

  	if(vm->checkResponse())
  	{
      Serial.print("RESPONSE: ");
  		for(int i = 0; i < vm->getOpCodeLength(); i++)
  		{
  			Serial.print(vm->getOpCode()[i]);
  		}
      Serial.println("");

      switch(vm->getOpCode()[0]){

        case 'v':
          bool good = false;
          switch(vm->getOpCode()[1]){
            case 'w':
              //water
              good = vm->vend(WATER);
              break;
            case 'r':
              //gat red
              good = vm->vend(GATORADE_RED);
              break;
            case 'b':
              //gat blue
              good = vm->vend(GATORADE_BLUE);
              break;
            case 'y':
              //gat yellow
              good = vm->vend(GATORADE_YELLOW);
              break;
            case 'o':
              //gat orange
              good = vm->vend(GATORADE_ORANGE);
              break;
          }

          vm->getClient().sendData("{\"success\": "+std::string(good ? "true" : "false")+" }");
          break;

      }
  	}
  	delay(500);
}
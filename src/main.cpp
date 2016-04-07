#include "../inc/main.h"


#define NUMBER_OF_DISPENSERS 4

VendingMachine * vm;

int dispenserPins[4] = {2, 4, 17, 22};

std::string host = "tgauch.net";

std::string ID = "vendfit_machine_1";

int port = 8888;

// convert a few characters to ints
int char2int(char val) {
  return (val-'0');
}
int char2int(char val, char val2) {
  return ((val-'0')*10)+(val2-'0');
}
int char2int(char val, char val2, char val3) {
  return ((val-'0')*100)+((val2-'0')*10)+(val3-'0');
}

ItemType getItemType(int id){
  switch(id)
  {
      case 0:
        //water
        return WATER;
      case 1:
        //gat red
        return GATORADE_RED;
      case 2:
        //gat blue
        return GATORADE_BLUE;
      case 3:
        //gat yellow
        return GATORADE_YELLOW;
      case 4:
        //gat orange
        return GATORADE_ORANGE;
      default:
        return WATER;
  }
}

void setup() 
{ 
  	vm = new VendingMachine(ID, NUMBER_OF_DISPENSERS, dispenserPins);

  	vm->initClient(host, port);
  	vm->registration();
} 


void loop() 
{ 
  	vm->stayAlive();
    int hasResponse = vm->parseResponse();
    if(hasResponse < 0){
      vm->registration();
    }else if(hasResponse > 0)
    {
      std::cout << "RESPONSE: ";
  		for(int i = 0; i < vm->getOpCodeLength(); i++)
  		{
  			std::cout << vm->getOpCode()[i];
  		}
      std::cout << std::endl;

      switch(vm->getOpCode()[0]){
        case 'v':
          {
            bool good = vm->vend(char2int(vm->getOpCode()[1]));
            vm->getClient().sendData("{\"operation\":\"machine_vend_response\", \"data\": {\"success\": "+std::string(good ? "true" : "false")+" }}");
            break;
          }
        case 'c':
          vm->checkin();
          break;
        case 'r':
          vm->registration();
          break;
        case 'd':
          vm->updateDispenser(char2int(vm->getOpCode()[1]), char2int(vm->getOpCode()[3], vm->getOpCode()[4]), getItemType(char2int(vm->getOpCode()[2])));
          break;
      }
  	}
}

int main(){
  signal(SIGPIPE, SIG_IGN);
  setup();
  while(true) loop();
}

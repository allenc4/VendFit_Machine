#include "VendFitClient.h"

VendFitClient::VendFitClient(IPAddress ip, int port){
	this->ip = ip;
	this->port = port;
	Serial.begin(9600);
}

void VendFitClient::connect(){
	this->stayConnected();
}

void VendFitClient::stayConnected(){
	while(!this->client.connected())
    {
    	Serial.print("Connecting..with(");
    	Serial.print(this->ip);
    	Serial.print(":");
    	Serial.print(this->port);
    	Serial.println(")");
 	   	this->client.connect(this->ip, this->port);
        if(!this->client.connected())
        {
        	Serial.println("Couldn't Connect");
            delay(1000);
            this->client.stop();
        }
    }
}

void VendFitClient::sendData(std::string content){
	content+=this->END;
	client.write(content.c_str());
    client.flush();
}

void VendFitClient::parseResponse(char &opcode, int length){
	// do{
 //      if(Serial.available() > 0 && processing == false)
 //     {
 //        incomingByte = Serial.read();

 //        Serial.print("Received: ");
 //        Serial.println(incomingByte);

 //        if(currentIndex > NUMBER_OF_BYTES)
 //        {
 //            Serial.print("ERROR: Invalid code.  Code Length max (");
 //            Serial.print(NUMBER_OF_BYTES);
 //            Serial.println(")");
 //            currentIndex = 0;
 //        }else
 //        {
 //            if(incomingByte == 10)
 //            {
 //              break;
 //            }else
 //            {
 //                opcode[currentIndex] = incomingByte;
 //                currentIndex++;
 //            }
 //        }
 //     }
 //  }while(incomingByte != 10);

 //  incomingByte = 0;
 //  currentIndex = 0;
 //  processing = true;

 //  for(int i = 0; i < NUMBER_OF_BYTES; i++)
 //  {
 //      if(opcode[i] == 10)
 //      {
 //        break;
 //      }
      
 //      Serial.print(opcode[i]);
 //  }

 //  switch(opcode[0])
 //  {

 //      case 'v':
 //          vend(opcode[1]-48); //convert from ascii to decimal 48 is ascii for 0
 //          processing = false;
 //        break;
 //      default:
 //        Serial.print("ERROR: Invalid opcode (");
 //        Serial.print(opcode[0]);
 //        Serial.println(")");
 //        processing = false;
 //        break;

 //  }
}
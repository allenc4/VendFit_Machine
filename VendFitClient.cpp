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
        }
    }
}

void VendFitClient::sendData(std::string content){
	content+=this->END;
	client.write(content.c_str());
    client.flush();
}

void VendFitClient::flush()
{
	long startTime = millis();
	while (client.available() == false && millis() - startTime < 1000) {
		// Just wait up to 1000 millis
	}
	startTime = millis();
	while (client.available() > 0 && millis() - startTime < 1000) {
	client.read();
	}
}

bool VendFitClient::parseResponse(char * opcode, int length){
	int incomingByte = 0;
	int currentIndex = 0;
	long startTime = millis();
	while(this->client.available() && incomingByte != 10 && currentIndex < length && millis() - startTime < 5000)
	{
		incomingByte = client.read();
		if(currentIndex >= length)
		{
			currentIndex = 0;
			this->flush();
			this->sendData("{\"success\": false, \"message\":\"Invalid opcode\"}");
			Serial.println("Invalid opcode");
			return false;
		}else
		{
			if(incomingByte == 10)
			{
				break;
			}else
			{
				opcode[currentIndex] = incomingByte;
		        currentIndex++;
			}
		}
	}

	if(currentIndex > 0)
	{
		return true;
	}
	return false;
}
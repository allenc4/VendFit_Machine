#include "main.h"

#define NUMBER_OF_SERVOS 4
#define NUMBER_OF_BYTES 8

Servo s1;
Servo s2;
Servo s3;
Servo s4;

Servo servos[NUMBER_OF_SERVOS];
         
int currentIndex = 0;

char opcode[NUMBER_OF_BYTES];
char incomingByte = 0;
bool processing = false;


void vend(int servo);


void setup() 
{ 
	Serial.begin(9600);
  servos[0].attach(A0);
  servos[1].attach(A1);
  servos[2].attach(A4);
  servos[3].attach(A5);

  for(int i = 0; i < NUMBER_OF_SERVOS; i++)
  {
      servos[i].write(180);
  }

  Serial.println("Setup complete");
} 


void loop() 
{ 
  do{
      if(Serial.available() > 0 && processing == false)
     {
        incomingByte = Serial.read();

        Serial.print("Received: ");
        Serial.println(incomingByte);

        if(currentIndex > NUMBER_OF_BYTES)
        {
            Serial.print("ERROR: Invalid code.  Code Length max (");
            Serial.print(NUMBER_OF_BYTES);
            Serial.println(")");
            currentIndex = 0;
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
  }while(incomingByte != 10);

  incomingByte = 0;
  currentIndex = 0;
  processing = true;

  for(int i = 0; i < NUMBER_OF_BYTES; i++)
  {
      if(opcode[i] == 10)
      {
        break;
      }
      
      Serial.print(opcode[i]);
  }

  switch(opcode[0])
  {

      case 'v':
          vend(opcode[1]-48); //convert from ascii to decimal 48 is ascii for 0
          processing = false;
        break;
      default:
        Serial.print("ERROR: Invalid opcode (");
        Serial.print(opcode[0]);
        Serial.println(")");
        processing = false;
        break;

  }

}

void vend(int servo)
{
    if(servo > 0 && servo < NUMBER_OF_SERVOS + 1)
    {
        servos[servo-1].write(0);
        delay(1000);
        servos[servo-1].write(180);
    }
}
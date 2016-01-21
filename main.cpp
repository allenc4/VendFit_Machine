#include "main.h"

Servo s1;
Servo s2;
Servo s3;
Servo s4;
         

int pos = 0;

void setup() 
{ 
	Serial.begin(9600);
  	s1.attach(A0);  
  	s2.attach(A1);  
  	s3.attach(A4);  
  	s4.attach(A5);  
} 


void loop() 
{ 
  for(pos = 0; pos < 180; pos++)  
  {                               
    s1.write(pos);  
    s2.write(pos);  
    s3.write(pos);  
    s4.write(pos);  
    Serial.println(pos);          
    delay(15);                    
  } 
  for(pos = 180; pos>0; pos--)    
  {                                
    s1.write(pos);  
    s2.write(pos);  
    s3.write(pos);  
    s4.write(pos);             
    Serial.println(pos);
    delay(15);                    
  } 
}
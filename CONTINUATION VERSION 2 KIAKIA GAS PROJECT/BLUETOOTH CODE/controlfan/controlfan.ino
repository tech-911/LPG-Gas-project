#include <SoftwareSerial.h>
SoftwareSerial BT(0, 1); //TX, RX  pins of arduino respetively
String command;
void setup()
{
 BT.begin(9600);
 Serial.begin(9600);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12,OUTPUT); 

     digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
}

void loop() {
  while (BT.available()){  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable
  char c = BT.read(); //Conduct a serial read
  command += c; //build the string.
  }
  if (command.length() > 0) {
    Serial.println(command);
  
  if(command == "A") //this command will be given as an input to speed one
  {
    digitalWrite(10, HIGH); 
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);

  }
  else if(command == "B") //this command will be given as an input to speed two
  {
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);

  }
  else if (command == "C") //this command will be given as an input to speed two
  {
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
   
  }
  else if ( command == "D") //this command will be given as an input to off the fan
 {
   digitalWrite (10, LOW);
   digitalWrite(11, LOW);
    digitalWrite(12, LOW);
   
 }
 
command="";}} //Reset the variable

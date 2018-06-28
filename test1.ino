#include <SoftwareSerial.h>
#define DEBUG true
SoftwareSerial esp8266(2,3); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
// This means that you need to connect the TX line from the esp to the Arduino's pin 2
// and the RX line from the esp to the Arduino's pin 3
void setup()
{
Serial.begin(9600);
esp8266.begin(4800); // your esp's baud rate might be different
Serial.println("Ready!!");
sendData("AT+RST\r\n", 2000, DEBUG);
sendData("AT+CWMODE=3\r\n", 1000, DEBUG);
sendData("AT+CIFSR\r\n", 1000, DEBUG);
sendData("AT+CIPMUX=1\r\n", 1000, DEBUG);
sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG);
}
void loop()
{
if(esp8266.available()) // check if the esp is sending a message
{
if(esp8266.find("+IPD,"))
{
delay(1000); // wait for the serial buffer to fill up (read all the serial data)
// get the connection id so that we can then disconnect
int connectionId = esp8266.read()-48; // subtract 48 because the read() function returns
// the ASCII decimal value and 0 (the first decimal number) starts at 48
esp8266.find("first");
esp8266.write("first");
// make close command
String closeCommand = "AT+CIPCLOSE=";
closeCommand+=connectionId; // append connection id
closeCommand+="\r\n";
sendData(closeCommand,1000,DEBUG); // close connection
}
}
}

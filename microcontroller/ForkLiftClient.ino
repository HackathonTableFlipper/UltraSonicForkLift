/*
  Arduino Webserver using ESP8266
  Displays temperature in a webpage

  Arduino Mega has three Serial communication ports,this code works well with
  Arduino Mega.For UNO users,use Softserial library to connect ESP8266 with
  Arduino UNO
  If you're unsure about your Arduino model or its pin cofigurations,please check
  the documentation at http://www.arduino.cc

  modified August 2016
  By Joyson Chinta and Gladson Kujur

  modified October 2018
  by Jesko Edzards
 */

#include "Header/ForkLiftClient.h"
#include "Header/sonicClockMinimal.h"
#include "Header/protocol.h"

#define RX 10
#define TX 11
#define DEBUG true

#include <SoftwareSerial.h>
#include "Header/ESP.h"

String AP = "hackathon";
String PASS = "tomdockle";

const char line[] = "-----\n\r";
int loopCount=0;
char html[50];
char command[20];
char reply[500]; // you wouldn't normally do this

 char ipAddress [20];
 char name[30];
 int lenHtml = 0;
 char temp[5];

 SoftwareSerial esp8266(RX,TX);

void setup()
{
  Serial.begin(115200);  ///////For Serial monitor
  esp8266.begin(9600); ///////ESP Baud rate
  while (!Serial) {
    ; // wait for serial port to connect.
  }
  while (!esp8266) {
    ; // wait for serial port to connect.
  }

  //TODO check, if we can connect to a Wifi and the device is set
  //setupServer();

  //TODO if not: Open a server
  //setupClient();

  Serial.println(setupSonicClockMinimal());

  //logData(true, DateTime(1,1,1,1,1,1), DateTime(1,1,1,1,1,1));
}

void setupClient(){
	sendData("AT+CWMODE=1",200,false); // configure as access point
	sendData("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",200,true);
	sendData("AT+CIPMODE=0\r\n",200,true);
}

void setupServer(){
	int timeout = 4000;
	sendData("AT+CWMODE=3",timeout,false); // configure as access point
	sendData("AT+CWSAP=\"ESP_8266\",\"abcdefgh\",11,0",timeout,false);
	sendData("AT+CIPMUX=1",timeout,false); // configure for multiple connections
	sendData("AT+CIPSERVER=1,80",timeout,true); // turn on server on port 80
	sendData("AT+CIFSR",timeout,true); // get ip address
}

void loop()
{
	//handleClient();
	Serial.print(loopSonicClockMinimal());
}

void handleClient(){
	//TODO: argument finden, dass nur reagiert
//	if(esp8266.available()) // check if the ESP8266 is sending data
//	      {
//	          // this is the +IPD reply - it is quite long.
//	          // normally you would not need to copy the whole message in to a variable you can copy up to "HOST" only
//	          // or you can just search the data character by character as you read the serial port.
//	              // start sending the HTML
//	          	  //Serial.println("handle client");
//
//	              strcpy(html, "Hello\r\n");
//	              strcpy(command,"AT+CIPSEND=6,\r\n");
//	              esp8266.print(command);
//	              esp8266.print(html);
//	              esp8266.print("AT+CIPCLOSE=0\r\n");
//	              Serial.println("Done");
//	      }
//	      // drop to here and wait for next request.
}

  //////////////////////////////sends data from ESP to webpage///////////////////////////
int connectionId = 0;
 void espsend(String d)
         {
             String cipSend = " AT+CIPSEND=";
             cipSend += connectionId;
             cipSend += ",";
             cipSend +=d.length();
             sendData(cipSend,1000,DEBUG);
             sendData(d,1000,DEBUG);
         }

//////////////gets the data from esp and displays in serial monitor///////////////////////
String sendData(String command, const int timeout, boolean debug)
            {
                String response = "";
                esp8266.print(command + "\r\n");
                long int time = millis();
                while( (time+timeout) > millis())
                {
                   while(esp8266.available())
                      {
                         char c = esp8266.read(); // read the next character.
                         response+=c;
                      }
                }

                if(debug)
                     {
                     Serial.println("ESP: " + response); //displays the esp response messages in arduino Serial monitor
                     }
                return response;
            }


bool sendDataToRaspberry(int gabelstabler_id,bool, float startTime, float endTime){
	return false;
}

//const String getConfigPage(){
//	String webpage_index = "<!DOCTYPE html>" ;
//	webpage_index += "<html>";
//	webpage_index += "<head>";
//	webpage_index += "<title>Init Ultrasonic Frok Lift </title>";
////	webpage_index += "<style>";
////	webpage_index += ".content {max-width: 500px; margin: auto;}";
////	webpage_index += "form {width:\"25em\"; border: 1px solid gainsboro;}";
////	webpage_index += "input {margin: 0 0 1em 1em;}";
////	webpage_index += "label {float: left; text-align: right; width: 10em;}";
////	webpage_index += ".button {margin-left: 11em;}";
////	webpage_index += "</style>";
//	webpage_index += "</head>";
//	webpage_index += "<body>";
//	webpage_index += "<h1>Hello World!</h1>";
////	webpage_index += "<div class=\"content\">";
////	webpage_index += "<center>";
////	webpage_index += "<form>";
////	webpage_index += "<label for=\"ID\">";
////	webpage_index += "ID:";
////	webpage_index += "</label>";
////	webpage_index += "<input type=\"number\" id=\"ID\" min=\"0\" size=\"4\" required>";
////	webpage_index += "<br>";
////	webpage_index += "Please make sure that the used ID isn't already taken.";
////	webpage_index += "<label for=\"name\">Name:</label>";
////	webpage_index += "<input type=\"text\" id=\"name\"  maxlength=\"20\" required>";
////	webpage_index += "<br>";
////	webpage_index += "<label for=\"location\">Location:</label>";
////	webpage_index += "<input type=\"text\" id=\"location\" maxlength=\"20\" required>";
////	webpage_index += "<br>";
////	webpage_index += "<label for=\"ssid\">SSID:</label>";
////	webpage_index += "<input type=\"text\" id=\"ssid\" maxlength=\"32\" required><br>";
////	webpage_index += "<label for=\"password\">Password:</label>";
////	webpage_index += "<input type=\"password\" id=\"password\" maxlength=\"63\" required>"<br>";
////	webpage_index += "<p>";
////	webpage_index += "When you click on this button, the microcontroller will try connect to the specified Wi";
////	webpage_index += "<br>";
////	webpage_index += "If the connection can't be implemented within 2 minutes, ";
////	webpage_index += "the microcontroller will reset himself and open his own WiFi again.";
////	webpage_index += "</p>";
////	webpage_index += "<button type=\"button\" id=\"send\">Initialize the microcontroller</button>";
////	webpage_index += "<!-- TODO: Error message field -->";
////	webpage_index += "</form>";
////	webpage_index += "</center>";
////	webpage_index += "</div>";
//	webpage_index += "</body>";
//	webpage_index += "</html>";
//	webpage_index += "";
////
//	return webpage_index;
//}

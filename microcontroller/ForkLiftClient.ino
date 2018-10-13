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

SoftwareSerial esp8266(RX,TX);
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
  setupServer();

  //TODO if not: Open a server
  setupClient();

}

void setupClient(){
	sendData("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,false);
}

void setupServer(){
	int timeout = 4000;
	sendData("AT+CWMODE=3",timeout,false); // configure as access point
	sendData("AT+CWSAP=\"ESP_8266\",\"abcdefgh\",11,0",timeout,false);
	sendData("AT+CIPMUX=1",timeout,false); // configure for multiple connections
	sendData("AT+CIPSERVER=1,80",timeout,true); // turn on server on port 80
	sendData("AT+CIFSR",timeout,false); // get ip address
}

void loop()
{
	handleClient();
}

void handleClient(){
	if(esp8266.available()) // check if the ESP8266 is sending data
	      {
	          // this is the +IPD reply - it is quite long.
	          // normally you would not need to copy the whole message in to a variable you can copy up to "HOST" only
	          // or you can just search the data character by character as you read the serial port.
	          getReply( 2000 );
	              // start sending the HTML
	          	  //Serial.println("handle client");

	              strcpy(html,"Hello World\r\n");
	              strcpy(command,"AT+CIPSEND=0,12\r\n");
	              esp8266.print(command);
	              getReply( 2000 );
	              esp8266.print(html);
	              getReply( 2000 );
	              esp8266.print("AT+CIPCLOSE=0\r\n");
	      }
	      delay(100);
	      // drop to here and wait for next request.
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

void getReply(int wait)
{
    int tempPos = 0;
    long int time = millis();
    while( (time + wait) > millis())
    {
        while(esp8266.available())
        {
            char c = esp8266.read();
            if (tempPos < 500) { reply[tempPos] = c; tempPos++;   }
        }
        reply[tempPos] = 0;
    }
}


bool sendDataToRaspberry(int gabelstabler_id,bool, float startTime, float endTime){

}

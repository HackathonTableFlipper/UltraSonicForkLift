#include "../Header/ESP.h"

//const size_t MAX_MESSAGE_LENGHT = 2048;
//const char SEND_OK[] = "SEND OK";
//const char SEND_FAIL[] = "SEND FAIL";
//const char ERROR[] = "ERROR";
//
//request
//// https://stackoverflow.com/questions/41382845/how-to-post-http-request-with-arduino-esp8266-at-commands
bool request(String ip, String port, String message){

	sendData("AT+CIPSTART=4,\"TCP\",\"" + ip + "\","+ port,10,false);

	sendData("AT+CIPSEND=4," + message.length(),10,false);

	//TODO
	sendData("GET message",10,false);
			//"GET /pushingbox?devid=<DevID>&<field>=<value> HTTP/1.1\r\nHost: api.pushingbox.com\r\n"
}

//////////////gets the data from esp and displays in serial monitor///////////////////////
String sendData(String command, const int timeout, bool debug)
{
	String response = "";
	//esp8266.print(command + "\r\n");
	//TODO ggf korrigieren
	int time = 0;
	while( 400*timeout > time)
	{
	   while(false)//esp8266.available())
		  {
			 char c = ' ';//esp8266.read(); // read the next character.
			 response+=c;
		  }
	   ++time;
	}
	return response;
}
////
//setup
//
String get_MAC_ADDRESS(){
    /**
     * Response Fromat:
     *
     * +CIFSR:APIP,<SoftAP IP address>
     * +CIFSR:APMAC,<SoftAP MAC address>
     * +CIFSR:STAIP,<Station IP address>
     * +CIFSR:STAMAC,<Station MAC address>
     * OK
     */

    String response = sendCommand("AT+CIFSR");

    // get the line with the mac adress
    String mac = response.substring(44,44+12+5);
    // remove the :
    mac = mac.erase(std::remove(str.begin(), str.end(), ':'), str.end());

    return mac;
}
//
////////////////gets the data from esp and displays in serial monitor///////////////////////
//String sendData(String command, const int timeout=2000, bool debug=false)
//    {
//        String response = "";
//        esp8266.print(command + "\r\n");
//        long int time = millis();
//        while( (time+timeout) > millis())
//        {
//            while(esp8266.available())
//                {
//                    char c = esp8266.read(); // read the next character.
//                    response += c;
//                }
//        }
//
//        if(debug)
//                {
//                Serial.println("ESP: " + response); //displays the esp response messages in arduino Serial monitor
//                }
//        return response;
//    }

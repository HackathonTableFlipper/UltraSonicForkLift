#include "../Header/sonicClockMinimal.h"
#include "../Header/protocol.h"
#include "../Header/ESP.h"

//#include <string.h>
//#include <Ethernet.h>
//#include <stdio.h>
//#include <iostream>
//// #include <iomanip>

String serverIP = "172.16.7.71";
String serverPort = "9001";

//
///**
// * Sends a HTTP request to the server with the given JSON message
// * Try's five times, like specified in the doc (microcontrollerAPI.md)
// * returns true on succsess (200) and false on error.
// */
bool requestServer(String message){
    size_t len = message.length();
    if (len > 2048){
        // TODO: send in multiple parts (recursion)
        //"The length of the message was to long (len). Couldn't send.");
        return false;
    }

    // try to send the message to the server five times
    bool status = false;
    for(int i = 0; i < 5 && ! status; ++i){
        request(serverIP, serverPort, message);
    // TODO read response 200 or error?
        if(status) {
            break;
        }
    }
    return status;
}
//
///**
// * Perform the handshake with the server
// */
//bool setup(){
//    // collect the neccesary data
//    char type[] = "\"init\"";
//    char mac[] = "\"" + esp.get_MAC_ADRESS() + "\"";
//    char name[] = "\"" + name + "\"";
//    char location[] = "\"" + location + "\"";
//
//    // create the message
//    char message[] = "{" + TYPE + type + "," + MAC + mac + "," + NAME + "," + name + "," + LOCATION + location + "}";
//
//    // send the message
//    return request server(message);
//}
//

String dateTime2JSON(DateTime t){
	return String(t.year()) + "-" + String(t.month()) + "-" + String(t.day()) + " " + String(t.hour()) + ":" + String(t.minute()) + ":" + String(t.day());
}



enum savestate logData(bool loaded, DateTime starttime, DateTime endtime){
    // collect the neccesary data
    String mac = "";//"\"" + esp.get_MAC_ADRESS() + "\"";
    String type = "\"log\"";
    String data = "[{\"load\":" + String(loaded) + ", \"start\":" + dateTime2JSON(starttime) + "\"end\":" + dateTime2JSON(endtime) + "}]";

    // create the message
    String message = "{MAC " + mac + ",TYPE " + type + ", DATA" + data + "}";

    // send the message
    if(requestServer(message)){
    	return UPLOADED;
    }
    else{
    	//TODO: cache Data
    	//TODO: Send Data when reconnected to Wifi
    }
}

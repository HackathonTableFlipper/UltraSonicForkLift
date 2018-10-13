#include <string.h>
#include <Ethernet.h>
#include <stdio.h>
#include <iostream>
// #include <iomanip>


enum savestate {UPLOADED, CACHED, FAIL};

const char TYPE[] = "\"type\":";
const char MAC[] = "\"mac\":";
const char NAME[] = "\"name\":";
const char LOCATION[] = "\"location\":";
const char DATA[] = "\"data\":";

char serverIP[16];
char serverPort[5] = "8080";

String name;
String location;

/**
 * Sends a HTTP request to the server with the given JSON message
 * Try's five times, like specified in the doc (microcontrollerAPI.md)
 * returns true on succsess (200) and false on error.
 */
bool RequestServer(char message[]){
    size_t len = strlen(message);
    if (len > 2048){
        // TODO: send in multiple parts (recursion)
        println("The length of the message was to long (len). Couldn't send.");
        return false;
    }
    
    // try to send the message to the server five times
    bool status = false;
    for(int i = 0; i < 5 && ! status; ++i){
        status = sendToServer(message);
    esp.request("AT+CIPSEND=" + strlen(message), 
    serverIP,<remote port>])
    // TODO read response 200 or error?
        if(status) {
            break;
        }
    }
    return status;
}

/**
 * Perform the handshake with the server
 */
bool setup(){
    // collect the neccesary data
    char type[] = "\"init\"";
    char mac[] = "\"" + esp.get_MAC_ADRESS() + "\"";
    char name[] = "\"" + name + "\"";
    char location[] = "\"" + location + "\"";

    // create the message
    char message[] = "{" + TYPE + type + "," + MAC + mac + "," + NAME + "," + name + "," + LOCATION + location + "}";

    // send the message
    return request server(message);
}

char[] dateTime2JSON(DateTime t){
    char jsontime[20] = "0000-00-00 00:00:00";
    std::cout << std::setw(5) << std::setfill('0') << zipCode << std::endl;

}

enum savestate logData(bool loaded, DateTime starttime, DateTime endtime){
    // collect the neccesary data
    char mac[] = "\"" + esp.get_MAC_ADRESS() + "\"";
    char type[] = "\"log\"";
    char data[] = "[{\"load\":" + loaded + ", \"start\":" + starttime + \"end\":" + TODO + "]"; // TODO

    // create the message
    char message[] = "{" + MAC + mac + "," + TYPE + type + "," + DATA + data + "}";

    // send the message
    return request server(message);
}
/*
 * ForkLiftClient.h
 *
 *  Created on: 13.10.2018
 *      Author: jesko
 */

#ifndef HEADER_FORKLIFTCLIENT_H_
#define HEADER_FORKLIFTCLIENT_H_

#include<SoftwareSerial.h>

#define RX 10
#define TX 11
#define DEBUG true

void setupClient();
void setupServer();

//////////////////////////////sends data from ESP to webpage///////////////////////////
void espsend(String d);
String sendData(String command, const int timeout, boolean debug=false);
void getReply(int wait);
void handleClient();
bool sendDataToRaspberry(int gabelstabler_id,bool, float startTime, float endTime);





#endif /* HEADER_FORKLIFTCLIENT_H_ */

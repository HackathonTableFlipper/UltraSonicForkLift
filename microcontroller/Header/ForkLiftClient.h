/*
 * ForkLiftClient.h
 *
 *  Created on: 13.10.2018
 *      Author: jesko
 */

#ifndef HEADER_FORKLIFTCLIENT_H_
#define HEADER_FORKLIFTCLIENT_H_

void setupClient();
void setupServer();

//////////////////////////////sends data from ESP to webpage///////////////////////////
void espsend(String d);
void getReply(int wait);
void handleClient();

#endif /* HEADER_FORKLIFTCLIENT_H_ */

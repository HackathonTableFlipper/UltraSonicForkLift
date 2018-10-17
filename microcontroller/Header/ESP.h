/*
 * ESP.h
 *
 *  Created on: 14.10.2018
 *      Author: jesko
 */

#ifndef HEADER_ESP_H_
#define HEADER_ESP_H_

#include "../Header/sonicClockMinimal.h"

bool request(String ip, String port, String message);
String sendData(String command, const int timeout, bool debug=false);
String get_MAC_ADDRESS();



#endif /* HEADER_ESP_H_ */

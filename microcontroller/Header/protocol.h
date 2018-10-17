/*
 * protocol.h
 *
 *  Created on: 14.10.2018
 *      Author: jesko
 */

#ifndef HEADER_PROTOCOL_H_
#define HEADER_PROTOCOL_H_

#include <string.h>
#include <Ethernet.h>
#include <stdio.h>
//#include <iostream>
//#include <iomanip>

enum savestate {UPLOADED, CACHED, FAIL};

bool requestServer(String message);
String dateTime2JSON(DateTime t);
enum savestate logData(bool loaded, DateTime starttime, DateTime endtime);



#endif /* HEADER_PROTOCOL_H_ */

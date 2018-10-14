//
//
//const size_t MAX_MESSAGE_LENGHT = 2048;
//const char SEND_OK[] = "SEND OK";
//const char SEND_FAIL[] = "SEND FAIL";
//const char ERROR[] = "ERROR";
//
//request
//// https://stackoverflow.com/questions/41382845/how-to-post-http-request-with-arduino-esp8266-at-commands
//
//setup
//
//byte[4] get_MAC_ADRESS(){
//    return {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
//}
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

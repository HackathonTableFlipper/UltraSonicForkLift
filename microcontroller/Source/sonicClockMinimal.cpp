#include "../Header/sonicClockMinimal.h"

#define CALKEY 7
#define TRIGGER_PIN  12
#define ECHO_PIN     13
#define MAX_DISTANCE 13 //In centimeter
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
RTC_DS3231 rtc;

int16_t state=0,state2=0;
bool payloadState=true;


String setupSonicClockMinimal() {
	String returnStr = "setup sonicClockMinimal: ";
  Wire.begin();
  if (! rtc.begin()) {
	  returnStr += "Couldn't find RTC";
  }
  if (rtc.lostPower()) {
     returnStr += "RTC lost power, lets set the time!";
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  pinMode(CALKEY, INPUT); //Taster

  //Benötigt, damit der Taster zwischen high und low umschalten kann
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  digitalWrite(6,HIGH);
  digitalWrite(5,LOW);
  return returnStr;
}

String loopSonicClockMinimal() {
        delay(30);  //Nicht zu schnell mit dem Ultraschallsensor pingen
        String returnStr = "";
        //Debounce der Palette
        state = ((state<<1) | (sonar.ping()!=0)^payloadState | 0xe000);
        if (state==0xf000) {
          
        //RTC auslesen
          DateTime now = rtc.now();
          returnStr += now.unixtime() + "; ";
          
          //returnStr += now.unixtime() ":" + (payloadState ?": Ladung aufgenommen":": Ladung entfernt") + "; ";
          payloadState= !payloadState;
        }

        //Debounce des Tasters
        state2 = ((state2<<1) | digitalRead(CALKEY) | 0xfe00);
        if (state2==0xff00) {
                    
        //RTC auslesen
          DateTime now = rtc.now();
          returnStr += now.unixtime() + ": Taster gedrückt";
        }
        return returnStr;
}

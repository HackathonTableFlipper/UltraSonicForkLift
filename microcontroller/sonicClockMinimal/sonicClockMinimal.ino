#include <Wire.h>
#include "NewPing.h"
#include "RTClib.h"


#define CALKEY 7
#define TRIGGER_PIN  11
#define ECHO_PIN     12
#define MAX_DISTANCE 13 //In centimeter
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
RTC_DS3231 rtc;

int16_t state=0,state2=0;
bool payloadState=true;


void setup() {
  Wire.begin();
  Serial.begin(115200);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
  }
  if (rtc.lostPower()) {
     Serial.println("RTC lost power, lets set the time!");
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
}

void loop() {
        delay(30);  //Nicht zu schnell mit dem Ultraschallsensor pingen

        //Debounce der Palette
        state = ((state<<1) | (sonar.ping()!=0)^payloadState | 0xe000);
        if (state==0xf000) {
          
        //RTC auslesen
          DateTime now = rtc.now();
          Serial.print(now.unixtime());
          
          Serial.println(payloadState?": Ladung aufgenommen":": Ladung entfernt");
          payloadState= !payloadState;
        }

        //Debounce des Tasters
        state2 = ((state2<<1) | digitalRead(CALKEY) | 0xfe00);
        if (state2==0xff00) {
                    
        //RTC auslesen
          DateTime now = rtc.now();
          Serial.print(now.unixtime());
          
          Serial.println(": Taster gedrückt");
        }
}

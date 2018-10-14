#include "../Header/sonicClockMinimal.h"

#define DRIVESENS_PIN 7
#define TRIGGER_PIN  12
#define ECHO_PIN     13
#define MAX_DISTANCE 13 //In centimeter
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
RTC_DS3231 rtc;

int16_t state=0,state2=0;
bool payloadState=true;
bool isDriving=false;
unsigned long taskLastRun[3]={0, 0, 0};
unsigned long lastMove=0;
uint8_t drivCount=0;

DateTime startTime(0,0,0,0,0,0);

String setupSonicClockMinimal() {
  taskLastRun[0]=millis();
  String returnStr = "setup sonicClockMinimal: ";
  Wire.begin();
  if (! rtc.begin()) {
	  returnStr += "Couldn't find RTC\n";
  }
  if (rtc.lostPower()) {
     returnStr += "RTC lost power, lets set the time!\n";
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  pinMode(DRIVESENS_PIN, INPUT); //Taster

  //Benötigt, damit der Taster zwischen high und low umschalten kann
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  digitalWrite(6,HIGH);
  digitalWrite(5,LOW);

  pinMode(2,OUTPUT);
  digitalWrite(2,HIGH);

  return returnStr;
}

String loopSonicClockMinimal() {
  String returnStr = "";

  //Task 1, Erkennung der Ladung
  if(abs(millis()-taskLastRun[0])>30) {
    taskLastRun[0]=millis();
    
    //Debounce der Palette
    state = ((state<<1) | (sonar.ping()!=0)^payloadState | 0xe000);
    if (state==0xf000) {
      
    //RTC auslesen
    DateTime now = rtc.now();
    returnStr += String(now.unixtime()) + String((payloadState? ": Ladung aufgenommen":": Ladung entfernt")) + "\n";
    //logData(bool payloadState, DateTime starttime, DateTime endtime)
    payloadState= !payloadState;
    }
  }

  //Task 2, Bewegungserkennung für Fahrzustand
  if(abs(millis()-taskLastRun[1])>10) {
    taskLastRun[1]=millis();
    
    //Serial.print(digitalRead(DRIVESENS_PIN));
    
    if(digitalRead(DRIVESENS_PIN)) {
      if(isDriving==false) {
        
        if(drivCount>20) {
          DateTime now = rtc.now();
          returnStr += String(now.unixtime()) + ": Losgefahren\n";
          //logData(bool payloadState, DateTime starttime, DateTime endtime)
          isDriving=true;
          
        } else {
          drivCount++;
        }
      }
      
      lastMove=millis();
    }
    
    if((millis()-lastMove)>10000) {
      if(isDriving==true) {
        isDriving=false;
        DateTime now = rtc.now();
        returnStr+= String(now.unixtime()) + ": Angehalten\n";
        //logData(bool payloadState, DateTime starttime, DateTime endtime)
      }
      drivCount=0;
    }
  }
  return returnStr;
}

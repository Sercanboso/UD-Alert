/*
  Rx Pager Mini
  With Buzzer and Led
  
*/

#include <RCSwitch.h>

const int ButtonReset = 3;
const int LedFlashA = 12;
const int LedFlashB = 13;
const int SirenePin = 5;
const int RfModul = 0; // Receiver on interrupt 0 / Pin 2 on Arduino 328P
const int AlarmCode = 20191; // this is the transmitted code of the Belt
unsigned long TimeNow_One = 0;

boolean Alarm = false;



long int Counter=0;


RCSwitch mySwitch = RCSwitch();





void TheDelay(int Delay){
TimeNow_One = millis();
do {
    if (digitalRead(ButtonReset)== 0){ResetAlarm();Delay=0;}
   } while ((unsigned long)(millis() - TimeNow_One) < Delay); 

}



void ResetAlarm(){
  noTone(SirenePin);
  Alarm = false;
  digitalWrite(LedFlashA,LOW);
  digitalWrite(LedFlashB,LOW);
  
}

void BeepBeep(int Repeat) {
    for (int i = 0; i <= Repeat; i++) {
      digitalWrite(LedFlashA,LOW);
      digitalWrite(LedFlashB,HIGH);
      tone(SirenePin,4200);
      TheDelay(50);
      digitalWrite(LedFlashA,HIGH);
      digitalWrite(LedFlashB,LOW);
      noTone(SirenePin);  
      TheDelay(100);    
      }
     digitalWrite(LedFlashA,LOW);
     digitalWrite(LedFlashB,LOW);
}
void LedBlink(int Repeat,int Duration) {
    for (int i = 0; i <= Repeat; i++) {
      digitalWrite(LedFlashA,HIGH);
      digitalWrite(LedFlashB,LOW);
      TheDelay(Duration);
      digitalWrite(LedFlashA,LOW);
      digitalWrite(LedFlashB,HIGH);
      TheDelay(Duration);
      }
    digitalWrite(LedFlashA,LOW);
    digitalWrite(LedFlashB,LOW);
     
}

void setup() {
  analogReference(INTERNAL);
  Serial.begin(9600);
  mySwitch.enableReceive(RfModul);  // Receiver on interrupt 0
  pinMode(ButtonReset,INPUT_PULLUP);
  pinMode(SirenePin,OUTPUT);
  pinMode(LedFlashA,OUTPUT);
  pinMode(LedFlashB,OUTPUT);
  
  
  ResetAlarm();
  BeepBeep(0);
  
  
}

void loop() {

if (digitalRead(ButtonReset)== 0){ResetAlarm();}
if (Alarm == true) {Counter++;if (Counter > 50000) {LedBlink(2,200);Counter=0;}}

  
  if (mySwitch.available()) {      
      
      if (mySwitch.getReceivedValue() == AlarmCode){
                                                
                                                BeepBeep(3);
                                                Alarm = true;                                          
                                                
                                                }
                                                                                           
      
      
  mySwitch.resetAvailable();
                            }


 
}

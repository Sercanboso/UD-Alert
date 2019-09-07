/*
  Pampers Alert V01 Test
*/

#include <RCSwitch.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 11, 10, 9, 8); // RS, E, D4, D5, D6, D7
const int ButtonReset = 15;
const int SirenePin = 5;
boolean SireneOn = false;


RCSwitch mySwitch = RCSwitch();

void ResetAlarm(){
  noTone(SirenePin);
  
  lcd.setCursor(0, 1);
  lcd.print("Reset               ");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("All Clear               ");
}
void setup() {
  
  lcd.begin(16, 2);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
  pinMode(ButtonReset,INPUT);
  pinMode(SirenePin,OUTPUT);
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Pampers Check V1");
  ResetAlarm();
}

void loop() {
  
  if (digitalRead(ButtonReset)== 0){ResetAlarm();}
  
  if (mySwitch.available()) {      
      
      if (mySwitch.getReceivedValue() == 20191){
                                                
                                                tone(SirenePin,2400);
                                                lcd.setCursor(0, 1);
                                                lcd.print("Red Alert ");
                                                //lcd.print( mySwitch.getReceivedValue() );
                                                lcd.print("        ");
                                                delay(2500);
                                                noTone(SirenePin);                                               
                                                
                                                }
                                                                                           
      
      
  mySwitch.resetAvailable();
                            }
}

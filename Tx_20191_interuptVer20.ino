#include <RCSwitch.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/power.h>

RCSwitch mySwitch = RCSwitch();

const byte interruptPin = 0;
const int PowerRF = 3; 
const int DataPin = 4; 

void TransmitCode(int Code){
  digitalWrite(PowerRF,HIGH); //Power on, for the 433Mhz module
                            for (int i = 0; i <= 1; i++) {   //Repeat 2 times
                                                          
                                                          mySwitch.send(Code, 24);
                                                          delay(500); //Wait 800ms
                                                                                                                   
                                                          }
  digitalWrite(PowerRF,LOW); //Power off, for the 433Mhz module
}

void SleepAll() {
  delay(100);
  
  sei();                 // enables interrupts
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  power_all_disable ();  // power off ADC, Timer 0 and 1, serial interface
   
  sleep_enable();
  sleep_mode();  
  
  sleep_disable(); 
  power_all_enable ();
  
  
}
void setup() {
 
  pinMode(PowerRF,OUTPUT);
  GIMSK |= (1 << PCIE);   // pin change interrupt enable
  PCMSK |= (1 << PCINT0);
  ADCSRA = 0; // ADC uses ~320uA
  
  mySwitch.enableTransmit(DataPin); // Datapin on P4
  
}

void loop() {

SleepAll();
TransmitCode(20191);

}


ISR(PCINT0_vect) {
 // nothing to do
}

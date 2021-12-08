/* Author:      vojoel
 * Date:        01 Dec 2021
 * Description: RPM vs Duty Cycle
 */

#include <Wire.h>
#include <math.h>

unsigned int RPM = 0;
unsigned int duty = 255;
unsigned int duty_subtract = 5;
unsigned long revs; // # of tracked revolutions (will increase by 2/rev)
unsigned long last = 0; // to track time intervals between measurements

// Function to call when interrupted by signal
void addRev(){
  revs++;
} 

void setup()
{
    Serial.begin(9600);
    pinMode(11, OUTPUT);
    pinMode(3, INPUT);
    analogWrite(11, duty);

    // Interrupt when signal received
    // First parameter 1 means pin 3
    attachInterrupt(1, addRev, FALLING);
    // Wait 5s before starting measurement
    delay(5000);
}
 
void loop()
{
    // Prevent overflows
    if(duty - duty_subtract > 255) {
      duty = 255;
    }

    // All 100 revs, calculate RPM for this duty cycle and decrease by duty_subtract
    if(revs >= 100) {
      RPM = 30*1000/(millis() - last)*revs; // 30 because revs are counted twice per revolution
      last = millis();

      // Decrease duty cycle
      duty -= duty_subtract;
      analogWrite(11, duty);
      
      // Output RPM to Serial
      //Serial.print(duty);
      //Serial.print(" ");
      Serial.println(RPM);
      revs = 0;
    }
}

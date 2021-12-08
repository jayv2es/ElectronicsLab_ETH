/* Author:      vojoel
 * Date:        01 Dec 2021
 * Description: Implements a 2-point-controller for a fan with threshold 
 *              temperatures for both activating and deactivating the fan.
 */

#include <Wire.h>
#include <math.h>

const float R2 = 100000;    // Resistance at T0 (in Ohm)
const float R0 = (1023/510 - 1)*R2;   //R1 at T0
const float B = 4600;       // B-value in [4250K, 4299K]
const float T0 = 298.15;    // Room temperature 25°C

float threshold;           
float threshold_high;
float threshold_low;
float T_lower = 295;        // Lowest possible threshold in K (with potentiometer)
float T_upper = 315;        // Highest possible threshold in K (with potentiometer)
float V_meas;
float T;
float R;
bool state = 0;             // To save whether T above (1) Threshold or below (0)
 
void setup()
{
    Serial.begin(9600);
    pinMode(11, OUTPUT);
}
 
void loop()
{
    V_meas=analogRead(0);
 
    // Make Calculations (using eqs 8 and 9 in manual)
    R = (1023/V_meas - 1)*R0;
    T = 1/(log(R/R0)/B + 1/T0);

    // Converts angle of potentiometer to threshold temperature in [295K, 315K]
    threshold = analogRead(1);
    threshold_high = map(threshold, 0, 1023, T_lower, T_upper); // set to 300K for Task 20
    threshold_low = threshold_high - 2; // set to 298K for Task 20

    // Output data (comment-out unwanted)
    //Serial.print("T = ");
    Serial.println(T);        // Print T and state to Serial
    //Serial.print(",   Thr = ");
    //Serial.print(threshold_high); 
    //Serial.print(",   S = ");
    //Serial.println(state);
    
    // Sets duty cycle of fan to 100% if T above threshold
    if(T > threshold_high) {
      analogWrite(11, 255);
    }

    // Sets duty cycle of fan to 0% if T falls below threshold again
    if(T < threshold_low){
      analogWrite(11, 0);
    }    

    // Wait 1s
    delay(1000);
}

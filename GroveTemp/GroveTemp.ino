/* Author:      vojoel
 * Date:        29 Nov 2021
 * Description: Program to measure temperature with temperature sensor
 */

#include <math.h>
const float R0 = 100000;  // Resistance at T0 (in Ohm)
const float B = 4275;     // B-value in [4250K, 4299K]
const float T0 = 298.15;   // Room temperature 25°C
float V_meas;
float T;
float R;
int duty = 16;
 
void setup()
{
    Serial.begin(9600);
}
 
void loop()
{
    V_meas=analogRead(0);
 
    // Make Calculations (here we don't yet have confusion with R1,R2 from eqs. 7-9, i.e. we measure "R" and "R0" is set internally)
    R = (1023/V_meas - 1)*R0;
    T = 1/(log(R/R0)/B + 1/T0);

    // Print temperature
    Serial.println(T);  //println adds this parameter to plot

    // Wait 1s
    delay(1000);
}

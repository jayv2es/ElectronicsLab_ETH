/* Author:      vojoel
 * Date:        29 Nov 2021
 * Description: Program to measure temperature with temperature sensor and 
 *              output voltage drop over of thermistor (convert to T with Python
 *              after calibrating B-constant)
 */

#include <math.h>

// Used for sensor
const float R0 = 100000;  // Resistance at T0 (in Ohm)
const float B = 4275;     // B-value in [4250K, 4299K]
const float T0 = 298.15;   // Room temperature 25°C
float T;
float R;
float V_meas;

// Used for thermistor calculations in Python
float V_therm;

int duty = 16;
 
void setup()
{
    Serial.begin(9600);
    pinMode(5, INPUT);
}
 
void loop()
{
    V_meas=analogRead(0);
    V_therm=analogRead(5);
 
    // Make Calculations (here we don't yet have confusion with R1,R2 from eqs. 7-9, i.e. we measure "R" and "R0" is set internally)
    R = (1023/V_meas - 1)*R0;
    T = 1/(log(R/R0)/B + 1/T0);

    // Print temperature
    Serial.print(T);
    Serial.print(" ");
    Serial.println(V_therm); 

    // Wait 1s
    delay(1000);
}

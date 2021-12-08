/* Author:      vojoel
 * Date:        29 Nov 2021
 * Description: Program to measure temperature with temperature sensor and output on LCD
 */

#include <Wire.h>
#include <rgb_lcd.h>
#include <math.h>

rgb_lcd lcd;
const float R0 = 100000;    // Resistance at T0 (in Ohm)
const float B = 4275;       // B-value in [4250K, 4299K]
const float T0 = 298.15;    // Room temperature 25°C
const float threshold = 297; // Threshold above which 
float V_meas;
float T;
float R;
bool red = 1;
 
void setup()
{
    lcd.begin(16,2);
    lcd.print("Temperature T:");
    
}
 
void loop()
{
    V_meas=analogRead(0);
 
    // Make Calculations (using eqs 8 and 9 in manual)
    R = (1023/V_meas - 1)*R0;
    T = 1/(log(R/R0)/B + 1/T0);

    // Reset LCD and print temperature
    lcd.setCursor(0,1);
    lcd.print(T);  //println adds this parameter to plot

    if(T > threshold) {
      lcd.setRGB(255,0,0);
      red = 1;
    }

    if(red == 1 and T < threshold){
      lcd.setRGB(0,0,255);
      red = 0;
    }
    

    // Wait 1s
    delay(1000);
}

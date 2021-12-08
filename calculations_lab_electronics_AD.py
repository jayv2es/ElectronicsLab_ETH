# -*- coding: utf-8 -*-
"""
Created on Mon Nov 29 20:17:47 2021

@author: joel9
"""

import numpy as np
from scipy.optimize import fsolve

### UNCERTAINTY CALCULATION (ex 14)

# Known uncertainties
dB = 138
dR0 = 0.01*100000 #1% uncertainty on 100kOhm
dV_meas = 5.01 # Resolution = 4.9mV per unit -> dV = 4.9/1000 * 1023

# Initialize values
R0 = 100000 # Ohm
V_meas = 494 #V (this is the adjusted voltage using eq. 8, i.e. Arduino Output)
B = 4600
R = R0 * (1023./V_meas - 1.)
T0 = 25 + 273.15 #K

# Calculate using Gaussian error propagation
dR = np.sqrt((1023*R0/V_meas**2)**2*dV_meas**2 + (1023./V_meas - 1)**2*dR0**2)

dT = np.sqrt(((T0**2 * np.log(R/R0))/(B + T0 * np.log(R/R0))**2)**2 * dB**2
             + (B*T0**2/(R*(B + T0 * np.log(R/R0))**2))**2 * dR**2
             + (B*T0**2/(R0*(B + T0 * np.log(R/R0))**2))**2 * dR0**2)



### CALIBRATE B (ex 15)

T_sensor = 297.44 # Measured T from Temperature Sensor (+/- 4K)
V_therm = 507 # Voltage measured after thermistor (+/- 1V)
R0_therm = (1023./510 - 1)*100000 #R1 at T0, compare Arduino Sketch
R_therm =  R0_therm * (1023.0 / V_therm - 1.0)
T_therm = lambda B_new: 1./(np.log(R_therm/R0_therm)/B_new + 1./T0) - T_sensor

# Solve T_therm for zeros to get new B-value, using B as start value
B_new = fsolve(T_therm, B)

# Error calculation B (Gaussian error propagation)
dV_therm = 1
dT_sensor = 4
# We can use dV_therm = dV_meas here, since its the same uncertainty.
# R0 here is "R2" from the equations, yielding "R0" from the equation as "R0_therm"
dR0_therm = np.sqrt((1023*R0/V_therm**2)**2*dV_meas**2 + (1023./V_therm - 1)**2*dR0**2)
dR_therm = np.abs(-R0_therm*(1023./(V_therm)**2)*dV_therm)
dB_new = np.sqrt(((T0*T_sensor/(T0*R + R*T_sensor)*dR_therm)**2 + 
                 ((T0**2*np.log(R/R0))/((T0+T_sensor)**2)*dT_sensor)**2 +
                 (T0*T_sensor)/(T0*R0 + R0*T_sensor))**2)



### RESISTANCE CALCULATION (ex 16)

P_wanted = 0.25 #W
R_needed = 5**2/P_wanted #since P := V^2 / R, and V = V_in = 5V



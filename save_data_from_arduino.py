# -*- coding: utf-8 -*-
"""
Helper code to save and plot data from Arduino measurements
"""

from serial import Serial
import pandas as pd
from datetime import datetime
import time
import matplotlib.pyplot as plt
import numpy as np
import time

# Init
res = {}
res['Measurement'] = {}
res['Timestamp'] = {}


def save_data(res, maxit, timeint):
    '''
    Fills up res-dictionary with T-measurements from Arduino.

    Parameters
    ----------
    res : Resulting dictionary storing measurements and timestamps
    maxit : Positive integer, how many datapoints to collect
    timeint : Positive float, how long to wait in seconds before collecting
              next data point
    Returns
    ----------
    Resulting array as DataFrame
    '''
    i = 0
    arduino = Serial('COM5', 9600)
    while(i<maxit):        
        line = arduino.readline()
        T = float(line[0:len(line)].decode('utf-8'))
        print("Iteration: " + str(i) + "   /   Measurement: " + str(T))
        res['Measurement'][i] = T
        res['Timestamp'][i] = str(datetime.now())
        time.sleep(timeint)
        i += 1
    arduino.close()
    return res


def plot_output(filename, savename, task_nr, xlabel, ylabel):
    '''
    Plots data from Excel-file and saves as PNG.

    Parameters
    ----------
    filename : xlsx-File to import with cols 'Measurement | Timestamp'
    savename : name to save as PNG
    '''
    rpm = np.array([0, 200, 400, 700, 1000, 1300, 1600, 1900])
    Teq = np.array([303.91, 300.49, 299.951, 298.68, 298.11, 297.78, 297.46, 297.38])
    plt.figure(figsize=(20, 12))
    plt.plot(rpm, Teq, 'r-o')
    plt.grid()
    plt.title('Equilibrium Temperature for different RPM')
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.savefig(savename)
    plt.show()
    pass


# CONFIG
task_nr = 24
maxit = 48
timeint = 0.
xlabel = 'RPM'
ylabel = 'Temperature / K'

# ARRAYS  T24


# MAIN
filename = 'Arduino_Task'+str(task_nr)+'.xlsx'
savename = 'Ex24_RPM-vs-EqTemp.png'
measurements = save_data(res, maxit, timeint)
pd.DataFrame(measurements).to_excel(filename)
time.sleep(5)
plot_output(filename, savename, task_nr, xlabel, ylabel)








    
        
    
    
    
    

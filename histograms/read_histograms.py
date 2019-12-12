#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Nov  5 16:33:28 2019

@author: thomas
"""
### Python modules
from os import path
import numpy as np
import matplotlib.pyplot as plt


def read(file_name):

    if check_histograms(file_name):
        the_intensities = np.array([0 for i in range(256)])
        f = open(file_name,"r")
        intensity = 0
        
        for line in f:
            string = ''
            for figure in line:
                string += figure
            the_intensities[intensity] = int(string)
            intensity +=1
            
        f.close()
        return the_intensities




def check_histograms(file_name): # Check if the histograms exists and has the good size
    if not path.exists(file_name): # The file doesn't exist yet, it has to be created.
        return (False)
    else:
        f = open(file_name,"r")
        nb_intensity = 0
        for line in f:
            nb_intensity += 1
        f.close()
        return (nb_intensity==256)



#lenna = read("lenna.txt")
#plt.plot(lenna)

red_mandrill = read("red_mandrill.txt")
plt.plot(red_mandrill, 'r')

green_mandrill = read("green_mandrill.txt")
plt.plot(green_mandrill, 'g')

blue_mandrill = read("blue_mandrill.txt")
plt.plot(blue_mandrill, 'b')
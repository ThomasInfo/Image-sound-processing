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




def plot_histogram(file_name, color, title_name): ## color is the character defining the color of the Channel
    histo = read(file_name)
    
    if color == 'k': ## black
        lab = 'Grayscale histogram'
    elif color == 'r':
        lab = 'Red histogram'
    elif color == 'g':
        lab = 'Green histogram'
    elif color == 'b':
        lab = 'Blue histogram'
    else:
        raise NameError('Color should be either "k", "r", "g", or "b".')
    
    plt.plot(histo, color, label = lab)
    plt.xlabel('Color intensity')
    plt.ylabel('Number of pixels')
    plt.legend()
    plt.title(title_name)
    
    save_name = file_name[:-4] + '_histogram'
    plt.savefig(save_name)
    plt.close()
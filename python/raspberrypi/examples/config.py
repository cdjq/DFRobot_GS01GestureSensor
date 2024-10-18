'''
  @file config.py
  @brief Configure sensor parameters
  @details  This code configures the sensor's address and serial communication parameters.
  @copyright   Copyright (c) 2024 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license     The MIT license (MIT)
  @author [fengli](li.feng@dfrobot.com)
  @version  V1.0
  @date  2024-08-09
  @https://github.com/DFRobot/DFRobot_GS01GestureSensor
'''

# -*- coding: utf-8 -*-

import smbus
import time
import serial
import sys
sys.path.append("../")
from DFRobot_GS01GestureSensor import DFRobot_GS01GestureSensor_I2C, DFRobot_GS01GestureSensor_UART

# Define macros (simulated using variables)
USE_I2C = False  # Set to True to use I2C; set to False to use UART

# Define device address and baud rate
DEVICE_ID = 0x72
UART_BAUD_RATE = 9600

# Choose between I2C or UART based on the macro
if USE_I2C:
    # Using I2C interface
    cs01 = DFRobot_GS01GestureSensor_I2C(bus=1, addr=DEVICE_ID)  # Assuming I2C bus 1 is used
else:
    # Using UART interface
    cs01 = DFRobot_GS01GestureSensor_UART(baud=UART_BAUD_RATE, addr=DEVICE_ID)

def setup():
    """
    @brief Setup function for initializing the sensor and communication.
    
    This function initializes the sensor and configures the communication settings
    based on the selected interface (I2C or UART).
    """
    if USE_I2C:
        # I2C does not require additional initialization
        print("I2C setup complete.")
    else:
        # Configure UART communication
        cs01.config_uart(baud=UART_BAUD_RATE, parity=0, stop_bit=2)
        print("UART configured.")
    
    # Set the device address
    cs01.set_addr(DEVICE_ID)
    print("Device address set to: {}".format(DEVICE_ID))

def loop():
    """
    @brief Main loop function.
    
    This function runs in a loop, simulating a delay similar to Arduino's delay function.
    """
    while True:
        time.sleep(1)  # Simulate delay similar to Arduino's delay function

# Execute the setup function
setup()

# Execute the loop function
loop()

/*!
 *@file config.ino
 *@brief Configure sensor parameters
 *@details  This code configures the sensor's address and serial communication parameters.
 *@copyright   Copyright (c) 2024 DFRobot Co.Ltd (http://www.dfrobot.com)
 *@license     The MIT license (MIT)
 *@author [fengli](li.feng@dfrobot.com)
 *@version  V1.0
 *@date  2024-08-09
 *@https://github.com/DFRobot/DFRobot_GS01GestureSensor
*/

#include "DFRobot_GS01GestureSensor.h"

// Define the device ID for the GS01 sensor
#define DEVICE_ID  0x72 

// Create an instance of DFRobot_GS01GestureSensor_UART with the specified device ID and Serial1 for UART communication
DFRobot_GS01GestureSensor_UART cs01(&Serial1, DEVICE_ID);


void setup(){
    // Initialize Serial1 for UART communication with the GS01 sensor
    Serial1.begin(9600);

    // Initialize serial communication for debugging purposes 
    Serial.begin(115200);

    // Configure the UART settings of the GS01 sensor
    cs01.configUart(eBaud_115200, UART_CFG_PARITY_NONE, UART_CFG_STOP_BITS_2);

    // Set the device address of the GS01 sensor
    cs01.setDeviceAddr(0x72);
}


void loop()
{
    // Main loop code would go here
}

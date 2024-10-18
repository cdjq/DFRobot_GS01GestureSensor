/*!
 *@file getPidVid.ino
 *@brief Retrieve the device's PID and VID
 *@details  This code demonstrates how to retrieve and display the Product ID (PID) and Vendor ID (VID) of the DFRobot GS01 sensor. It also shows how to get the number of detected faces.
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

// Create an instance of DFRobot_GS01GestureSensor_I2C with the specified device ID
DFRobot_GS01GestureSensor_I2C cs01(DEVICE_ID);


void setup(){
    // Initialize I2C communication
    cs01.begin(&Wire);

    // Initialize serial communication for debugging purposes
    Serial.begin(115200);

    // Retrieve and print the Product ID (PID) of the GS01 sensor
    Serial.println(cs01.getGs01Pid());

    // Retrieve and print the Vendor ID (VID) of the GS01 sensor
    Serial.println(cs01.getGs01Vid());
}


void loop(){
    // Retrieve and print the number of faces detected
    Serial.println(cs01.getFaceNumber());

    // Delay before the next loop iteration
    delay(1500);
}

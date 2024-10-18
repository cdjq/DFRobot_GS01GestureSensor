/*!
 *@file detectGesture.ino
 *@brief Detect gestures
 *@details  This code detects the location, score of faces, and gestures along with their scores.
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

// Buffer for formatted output
char str[100];


void setup(){
    // Initialize Serial1 for UART communication with the GS01 sensor
    Serial1.begin(9600);

    // Initialize serial communication for debugging purposes
    Serial.begin(115200);

    // Set the face detection threshold. Face scores range from 0 to 100.
    // Faces with scores above this threshold will be detected.
    cs01.setFaceDetectThres(60);

    // Set the gesture detection threshold. Gesture scores range from 0 to 100.
    // Gestures with scores above this threshold will be detected.
    cs01.setGestureDetectThres(60);    

    // Set the gesture detection range.
    // The range is from 0 to 100; 0 has the smallest detection range, and 100 has the largest.
    cs01.setDetectThres(100);
}


void loop(){
    // Check if any faces are detected
    if(cs01.getFaceNumber() > 0){

        // Retrieve face score and location
        uint16_t faceScore = cs01.getFaceScore();
        uint16_t faceX = cs01.getFaceLocationX();
        uint16_t faceY = cs01.getFaceLocationY();
        
        // Print the face detection results
        sprintf(str, "detect face at (x = %d, y = %d, score = %d)\n", faceX, faceY, faceScore);
        Serial.print(str);
        
        // Print the gesture detection results
        // - 1: LIKE (👍) - blue
        // - 2: OK (👌) - green
        // - 3: STOP (🤚) - red
        // - 4: YES (✌) - yellow
        // - 5: SIX (🤙) - purple
        uint16_t gestureType = cs01.getGestureType();
        uint16_t gestureScore = cs01.getGestureScore();
        
        // Print the gesture detection results
        sprintf(str, "detect gesture %d, score = %d\n", gestureType, gestureScore);
        Serial.print(str);
    }
    
    // Delay before the next loop iteration
    delay(500);
}

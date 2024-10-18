/*!
 *@file DFRobot_GS01GestureSensor.cpp
 *@brief Define the basic structure of class DFRobot_GS01GestureSensor, the implementation of basic methods.
 *@details this module is used to identify the information in the QR code
 *@copyright   Copyright (c) 2024 DFRobot Co.Ltd (http://www.dfrobot.com)
 *@License     The MIT License (MIT)
 *@author [fengli](li.feng@dfrobot.com)
 *@version  V1.0
 *@date  2024-8-9
 *@https://github.com/DFRobot/DFRobot_GS01GestureSensor
*/

#include "DFRobot_GS01GestureSensor.h"
DFRobot_GS01GestureSensor::DFRobot_GS01GestureSensor()
{

}
uint16_t DFRobot_GS01GestureSensor::getGs01Pid()
{
    return reaInputdReg(REG_GS01_PID);
}
uint16_t DFRobot_GS01GestureSensor::getGs01Vid()
{
    return reaInputdReg(REG_GS01_VID);
}


uint16_t DFRobot_GS01GestureSensor::getFaceNumber(){
    return reaInputdReg(REG_GS01_FACE_NUMBER);
}	
uint16_t DFRobot_GS01GestureSensor::configUart(eBaudConfig_t baud,eParityConfig_t parity,eStopbits_t stopBit){
	uint16_t baudRate = baud;
	
	uint16_t verifyAndStop = ((uint16_t)parity<<8) | ((uint16_t)stopBit & 0xff);
	

	writeIHoldingReg(REG_GS01_BAUDRATE,baudRate);
	return writeIHoldingReg(REG_GS01_VERIFY_AND_STOP,verifyAndStop);
   	
}


uint16_t DFRobot_GS01GestureSensor::getFaceLocationX(){
    return reaInputdReg(REG_GS01_FACE_LOCATION_X);
}

uint16_t DFRobot_GS01GestureSensor::getFaceLocationY(){
    return reaInputdReg(REG_GS01_FACE_LOCATION_Y);
}
uint16_t DFRobot_GS01GestureSensor::getFaceScore(){
    return reaInputdReg(REG_GS01_FACE_SCORE);
}	
uint16_t DFRobot_GS01GestureSensor::getGestureType(){
    return reaInputdReg(REG_GS01_GESTURE_TYPE);
}
uint16_t DFRobot_GS01GestureSensor::getGestureScore(){
	
    return reaInputdReg(REG_GS01_GESTURE_SCORE);
}	



bool DFRobot_GS01GestureSensor::setFaceDetectThres(uint16_t score){
	
	
	return writeIHoldingReg(REG_GS01_FACE_SCORE_THRESHOLD,score);
	
}

bool DFRobot_GS01GestureSensor::setDetectThres(uint16_t x){
    return writeIHoldingReg(REG_GS01_FACE_THRESHOLD,x);
}  

bool DFRobot_GS01GestureSensor::setGestureDetectThres(uint16_t score){
	
	return writeIHoldingReg(REG_GS01_GESTURE_SCORE_THRESHOLD,score);
	
}


bool DFRobot_GS01GestureSensor::setDeviceAddr(uint16_t addr){
	    	
	return writeIHoldingReg(REG_GS01_ADDR,addr);
	
}








DFRobot_GS01GestureSensor_UART::DFRobot_GS01GestureSensor_UART(Stream *s_,uint8_t addr)
:DFRobot_RTU(s_){
  _addr = addr;
}


uint16_t DFRobot_GS01GestureSensor_UART::reaInputdReg(uint16_t reg)
{
    delay(20);
    return readInputRegister(_addr,reg);

}
uint16_t DFRobot_GS01GestureSensor_UART::readHoldingReg(uint16_t reg)
{
  delay(20);
  return readHoldingRegister(_addr,reg);

}
bool DFRobot_GS01GestureSensor_UART::writeIHoldingReg(uint16_t reg,uint16_t data){

     delay(20);
	 return writeHoldingRegister(_addr,reg,data);
}
bool DFRobot_GS01GestureSensor_UART::wirteReg(uint16_t reg,uint16_t data)
{
      return true;
}
uint16_t DFRobot_GS01GestureSensor_UART::readReg(uint16_t reg)
{
    //readInputRegister(_addr,reg)
	return 0;
}








DFRobot_GS01GestureSensor_I2C::DFRobot_GS01GestureSensor_I2C(uint8_t addr)
{
  _addr = addr;
}


bool DFRobot_GS01GestureSensor_I2C::begin(TwoWire *pWire)
{
	
  _pWire = pWire;
  pWire->setClock(100000);
  pWire->begin();
   pWire->setClock(100000);
  return true;
}
bool DFRobot_GS01GestureSensor_I2C::wirteReg(uint16_t reg,uint16_t data)
{
  uint16_t value;
  _pWire->beginTransmission(_addr);
  _pWire->write(reg>>8);
  _pWire->write(reg&0xff);
  
  _pWire->write(data>>8);
  _pWire->write(data&0xff);
  _pWire->endTransmission();
  delay(100);
  return true;
}
uint16_t DFRobot_GS01GestureSensor_I2C::readReg(uint16_t reg)
{
  uint16_t value;
  _pWire->beginTransmission(_addr);
  _pWire->write(reg>>8);
  _pWire->write(reg&0xff);
  _pWire->endTransmission();
  
  delay(50);
  
  _pWire->requestFrom(_addr,(uint8_t)2);
  delay(50);
  value = _pWire->read();
  value = value<<8 | _pWire->read();

  delay(100);
  
  if(value == 0x3636 || value == 0xffff) return 0;
  
  return value;
}
bool DFRobot_GS01GestureSensor_I2C::writeIHoldingReg(uint16_t reg,uint16_t data)
{
	
	
	
    return wirteReg(reg,data);
}
uint16_t DFRobot_GS01GestureSensor_I2C::reaInputdReg(uint16_t reg)
{
    return readReg(INPUT_REG_OFFSET+reg);
}

uint16_t DFRobot_GS01GestureSensor_I2C::readHoldingReg(uint16_t reg){
    return readReg(reg);
}


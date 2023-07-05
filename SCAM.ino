/*******************************************************************************
* Copyright 2016 ROBOTIS CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include <Dynamixel2Arduino.h>

#if defined(ARDUINO_OpenCM904) // When using official ROBOTIS board with DXL circuit.
  #define DXL_SERIAL   Serial3 //OpenCM9.04 EXP Board's DXL port Serial. (Serial1 for the DXL port on the OpenCM 9.04 board)
  #define DEBUG_SERIAL Serial
  const int DXL_DIR_PIN = 22; //OpenCM9.04 EXP Board's DIR PIN. (28 for the DXL port on the OpenCM 9.04 board)
#endif
 

const uint8_t DXL_ID = 4;
const float DXL_PROTOCOL_VERSION = 2.0;

float i_present_position = 0;
float f_present_position = 0;

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);

//This namespace is required to use Control table item names
using namespace ControlTableItem;

void setup() {
  // put your setup code here, to run once:
  
  // Use UART port of DYNAMIXEL Shield to debug.
  DEBUG_SERIAL.begin(115200);
  while(!DEBUG_SERIAL);

  // Set Port baudrate to 57600bps. This has to match with DYNAMIXEL baudrate.
  dxl.begin(1000000);
  // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  
  scam(1);
  scam(2);
  scam(3);
  scam(DXL_ID);
  scam(5);
  scam(6);

  scam(20);
  scam(19);
  scam(18);
  scam(17);
  scam(16);
  scam(15);

  scam(10); 
  scam(11);

 
  scam(12);
scam(13);
scam(14);

DEBUG_SERIAL.println();
DEBUG_SERIAL.println("=================================================================================");
}

void loop() {
  // put your main code here, to run repeatedly:

}

void scam(int DXL_ID_temp){

  // Get DYNAMIXEL information
  dxl.ping(DXL_ID_temp);

  // Turn off torque when configuring items in EEPROM area
  dxl.torqueOff(DXL_ID_temp);
  dxl.setOperatingMode(DXL_ID_temp, OP_POSITION);
  i_present_position = dxl.getPresentPosition(DXL_ID_temp);
  dxl.setGoalPosition(DXL_ID_temp, i_present_position);
  dxl.writeControlTableItem(POSITION_P_GAIN, DXL_ID_temp, 300);
  dxl.writeControlTableItem(POSITION_I_GAIN, DXL_ID_temp, 500);
  dxl.writeControlTableItem(POSITION_D_GAIN, DXL_ID_temp, 1000);
  dxl.torqueOn(DXL_ID_temp);

  delay(50);

  // Limit the maximum velocity in Position Control Mode. Use 0 for Max speed
  dxl.writeControlTableItem(PROFILE_VELOCITY, DXL_ID_temp, 10);
  // if(dxl.getTorqueEnableStat(DXL_ID_temp)) 
  //   DEBUG_SERIAL.println("Torque ON");
  // else
  //   DEBUG_SERIAL.println("Torque OFF");

  // DEBUG_SERIAL.print("DXL_ID - ");
  // DEBUG_SERIAL.println(DXL_ID_temp);
  
  DEBUG_SERIAL.print(int(i_present_position));
  DEBUG_SERIAL.print(", ");
}





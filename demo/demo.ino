#include <Dynamixel2Arduino.h>
#include <actuator.h>

#if defined(ARDUINO_OpenCM904) // When using official ROBOTIS board with DXL circuit.
  #define DXL_SERIAL   Serial3 //OpenCM9.04 EXP Board's DXL port Serial. (Serial1 for the DXL port on the OpenCM 9.04 board)
  #define DEBUG_SERIAL Serial
  const int DXL_DIR_PIN = 22; //OpenCM9.04 EXP Board's DIR PIN. (28 for the DXL port on the OpenCM 9.04 board)
#endif
 

const uint8_t DXL_ID_1 = 1;
const uint8_t DXL_ID_2 = 2;
const uint8_t DXL_ID_3 = 3;
const uint8_t DXL_ID_4 = 4;
const uint8_t DXL_ID_5 = 5;
const uint8_t DXL_ID_6 = 6;
const uint8_t DXL_ID_7 = 7;
const uint8_t DXL_ID_8 = 8;
const uint8_t DXL_ID_9 = 9;
const uint8_t DXL_ID_10 = 10;
const uint8_t DXL_ID_11 = 11;
const uint8_t DXL_ID_12 = 12;
const uint8_t DXL_ID_13 = 13;
const uint8_t DXL_ID_14 = 14;
const uint8_t DXL_ID_15 = 15;
const uint8_t DXL_ID_16 = 16;
const uint8_t DXL_ID_17 = 17;
const uint8_t DXL_ID_18 = 18;
const uint8_t DXL_ID_19 = 19;
const uint8_t DXL_ID_20 = 20;

const uint32_t left_leg[6] = { DXL_ID_1, DXL_ID_2, DXL_ID_3, DXL_ID_4, DXL_ID_5, DXL_ID_6 };
const uint32_t right_leg[6] = { DXL_ID_20, DXL_ID_19, DXL_ID_18, DXL_ID_17, DXL_ID_16, DXL_ID_15 };

// const uint32_t stand_ll[6] = { 7970, 8740, 9470, 6740, 7810, 8140 };
// const uint32_t stand_rl[6] = { 8360, 7958, 7300, 8860, 8360, 8290 };  горбатая поза

const uint32_t stand_ll[6] = { 8190, 8190, 8190, 8190, 8190, 8190 };
const uint32_t stand_rl[6] = { 8190, 8190, 8190, 8190, 8190, 8190 };    // стоит как солдатик

const float DXL_PROTOCOL_VERSION = 2.0;

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
  // Get DYNAMIXEL information

  // for (uint8_t j = 0; j < 6; j++) {

  //   if (dxl.ping(left_leg[j])) {
  //     DEBUG_SERIAL.println("ping success");
  //   } else {
  //     DEBUG_SERIAL.println("FUCK U");
  //   }

  //   // Turn off torque when configuring items in EEPROM area
  //   dxl.torqueOff(left_leg[j]);
  //   delay(10);
  //   dxl.setOperatingMode(left_leg[j], OP_POSITION);
  //   delay(10);
  //   dxl.torqueOn(left_leg[j]);
  //   delay(10);

  //   // Limit the maximum velocity in Position Control Mode. Use 0 for Max speed
  //   dxl.writeControlTableItem(81, left_leg[j], 30);  // 81 is register adress for velocity

  //   if (dxl.ping(right_leg[j])) {
  //     DEBUG_SERIAL.println("ping success");
  //   } else {
  //     DEBUG_SERIAL.println("FUCK U");
  //   }

  //   // Turn off torque when configuring items in EEPROM area
  //   dxl.torqueOff(right_leg[j]);
  //   delay(10);
  //   dxl.setOperatingMode(right_leg[j], OP_POSITION);
  //   delay(10);
  //   dxl.torqueOn(right_leg[j]);
  //   delay(10);

  //   // Limit the maximum velocity in Position Control Mode. Use 0 for Max speed
  //   dxl.writeControlTableItem(81, right_leg[j], 30);  // 81 is register adress for velocity
  // }

  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  dxl.ping(1);
  dxl.torqueOff(1);
  delay(10);
  dxl.setOperatingMode(1, OP_POSITION);
  delay(10);
  dxl.torqueOn(1);
  delay(10);
  dxl.writeControlTableItem(PROFILE_VELOCITY, 1, 30);

  dxl.ping(2);
  dxl.torqueOff(2);
  delay(10);
  dxl.setOperatingMode(2, OP_POSITION);
  delay(10);
  dxl.torqueOn(2);
  delay(10);
  dxl.writeControlTableItem(PROFILE_VELOCITY, 2, 30);

  dxl.ping(3);
  dxl.torqueOff(3);
  delay(10);
  dxl.setOperatingMode(3, OP_POSITION);
  delay(10);
  dxl.torqueOn(3);
  delay(10);
  dxl.writeControlTableItem(PROFILE_VELOCITY, 3, 30);

  dxl.ping(4);
  dxl.torqueOff(4);
  delay(10);
  dxl.setOperatingMode(4, OP_POSITION);
  delay(10);
  dxl.torqueOn(4);
  delay(10);
  dxl.writeControlTableItem(PROFILE_VELOCITY, 4, 30);

  dxl.ping(5);
  dxl.torqueOff(5);
  delay(10);
  dxl.setOperatingMode(5, OP_POSITION);
  delay(10);
  dxl.torqueOn(5);
  delay(10);
  dxl.writeControlTableItem(PROFILE_VELOCITY, 5, 30);

  dxl.ping(6);
  dxl.torqueOff(6);
  delay(10);
  dxl.setOperatingMode(6, OP_POSITION);
  delay(10);
  dxl.torqueOn(6);
  delay(10);
  dxl.writeControlTableItem(PROFILE_VELOCITY, 6, 30);

  dxl.ping(20);
  dxl.torqueOff(20);
  delay(10);
  dxl.setOperatingMode(20, OP_POSITION);
  delay(10);
  dxl.torqueOn(20);
  delay(10);
  dxl.writeControlTableItem(PROFILE_VELOCITY, 20, 30);

  dxl.ping(19);
  dxl.torqueOff(19);
  delay(10);
  dxl.setOperatingMode(19, OP_POSITION);
  delay(10);
  dxl.torqueOn(19);
  delay(10);
  dxl.writeControlTableItem(PROFILE_VELOCITY, 19, 30);

  dxl.ping(18);
  dxl.torqueOff(18);
  delay(10);
  dxl.setOperatingMode(18, OP_POSITION);
  delay(10);
  dxl.torqueOn(18);
  delay(10);
  dxl.writeControlTableItem(PROFILE_VELOCITY, 18, 30);

  dxl.ping(17);
  dxl.torqueOff(17);
  delay(10);
  dxl.setOperatingMode(17, OP_POSITION);
  delay(10);
  dxl.torqueOn(17);
  delay(10);
  dxl.writeControlTableItem(PROFILE_VELOCITY, 17, 30);

  dxl.ping(16);
  dxl.torqueOff(16);
  delay(10);
  dxl.setOperatingMode(16, OP_POSITION);
  delay(10);
  dxl.torqueOn(16);
  delay(10);
  dxl.writeControlTableItem(PROFILE_VELOCITY, 16, 30);

  dxl.ping(15);
  dxl.torqueOff(15);
  delay(10);
  dxl.setOperatingMode(15, OP_POSITION);
  delay(10);
  dxl.torqueOn(15);
  delay(10);
  dxl.writeControlTableItem(PROFILE_VELOCITY, 15, 30);

  dxl.ping(12);
  dxl.torqueOff(12);
  delay(10);
  dxl.setOperatingMode(12, OP_POSITION);
  delay(10);
  dxl.torqueOn(12);
  delay(10);
  dxl.writeControlTableItem(PROFILE_VELOCITY, 12, 30);

  dxl.ping(14);
  dxl.torqueOff(14);
  delay(10);
  dxl.setOperatingMode(14, OP_POSITION);
  delay(10);
  dxl.torqueOn(14);
  delay(10);
  dxl.writeControlTableItem(PROFILE_VELOCITY, 14, 30);

}


void loop() {
  // put your main code here, to run repeatedly:delay(10);

  for (uint8_t i = 0; i < 6; i++) {
    dxl.setGoalPosition(left_leg[i], stand_ll[i]);
    dxl.setGoalPosition(right_leg[i], stand_rl[i]);
  }

  hello();
}

void hello() {
  dxl.setGoalPosition(12, 16380);
  dxl.setGoalPosition(14, 8190);
  delay(1000);
  dxl.setGoalPosition(14, 10238);
  delay(1000);
}

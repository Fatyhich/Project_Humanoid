#include <Dynamixel2Arduino.h>

#if defined(ARDUINO_OpenCM904)  // When using official ROBOTIS board with DXL circuit.
#define DXL_SERIAL Serial3      //OpenCM9.04 EXP Board's DXL port Serial. (Serial1 for the DXL port on the OpenCM 9.04 board)
#define DEBUG_SERIAL Serial
const int DXL_DIR_PIN = 22;  //OpenCM9.04 EXP Board's DIR PIN. (28 for the DXL port on the OpenCM 9.04 board)
#endif

#define NUM_SERVOS 17
#define PROFILE_VELOCITY 81
#define POSITION_P_GAIN 43
#define POSITION_I_GAIN 44
#define POSITION_D_GAIN 45


const float DXL_PROTOCOL_VERSION = 2.0;

const uint8_t DXL_ID[NUM_SERVOS] = { 1, 2, 3, 4, 5, 6, 20, 19, 18, 17, 16, 15, 10, 11, 12, 13, 14 };  //IDs
long _lastmill = 0;
long _lastmill_head_1 = 0;
long _lastmill_head_2 = 0;

int32_t startPoints[] = { 8023, 8389, 8356, 7984, 7852, 7913, 8332, 7767, 7995, 8002, 8506, 8138, 8398, 1536, 12764, 7303, 8944 };
int32_t startArm[] = { 8023, 8389, 8356, 7984, 7852, 7913, 8332, 7767, 7995, 8002, 8506, 8138, 8398, 1536, 15588, 10655, 8937 };
int32_t moveHead[] = { 8097, 9032, 8795, 8402, 7964, 7652, 8227, 7029, 7170, 7960, 8525, 7985, 10139, 1561, 12494, 7872, 8199 };
int32_t leftHead[] = { 8055, 9073, 8914, 8360, 8050, 7343, 8211, 6612, 6792, 7936, 8635, 7991, 6803, 1557, 12492, 7867, 8219 };

unsigned long _currentTime;
unsigned long _lastUpdate;
uint8_t scenario = 0;
long Waving_T = 0;

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);

void setup() {
  // put your setup code here, to run once:

  DEBUG_SERIAL.begin(115200);
  delay(100);
  DEBUG_SERIAL.println("Start");
  // Set Port baudrate to 57600bps. This has to match with DYNAMIXEL baudrate.
  dxl.begin(1000000);
  // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  DEBUG_SERIAL.println("Set prot ver.");
  // Get DYNAMIXEL information

  for (int i = 0; i < NUM_SERVOS; i++) {

    dxl.ping(DXL_ID[i]);

    // Turn off torque when configuring items in EEPROM area
    dxl.torqueOff(DXL_ID[i]);
    dxl.setOperatingMode(DXL_ID[i], OP_POSITION);
    dxl.writeControlTableItem(PROFILE_VELOCITY, DXL_ID[i], 100);
    dxl.writeControlTableItem(POSITION_P_GAIN, DXL_ID[i], 300);
    dxl.writeControlTableItem(POSITION_I_GAIN, DXL_ID[i], 500);
    dxl.writeControlTableItem(POSITION_D_GAIN, DXL_ID[i], 1000);

    setStartPoint();

    dxl.torqueOn(DXL_ID[i]);
  }

  scenario = 0;
}

void loop() {
  //put your main code here, to run repeatedly:

  DEBUG_SERIAL.println(scenario);
  if (scenario == 3)
    scenario = 0;

  _currentTime = millis();

  switch (scenario) {
    case 0:
      while (_currentTime - _lastUpdate < 5000)
        _currentTime = millis();
      DEBUG_SERIAL.println("wait");
      _lastUpdate = _currentTime;
      break;
    case 1:
      setArmStart();
      while (_currentTime - _lastUpdate < 10000) {
        DEBUG_SERIAL.println("hand");
        dxl.setGoalPosition(DXL_ID[NUM_SERVOS - 1], 7831);
        delay(600);
        dxl.setGoalPosition(DXL_ID[NUM_SERVOS - 1], 11857);
        delay(600);
        _currentTime = millis();
      }
      break;
    case 2:
      setStartPoint();
      while (_currentTime - _lastUpdate < 10000) {
        DEBUG_SERIAL.println("head");
        setHead_Left();
        delay(2000);
        setHead_Right();
        delay(2000);
        _currentTime = millis();
      }
      setStartPoint();
      break;
  }
  
  _lastUpdate = _currentTime;
  scenario++;
}

void setStartPoint() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    dxl.setGoalPosition(DXL_ID[i], startPoints[i]);
    delay(10);
  }
}

void setArmStart() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    dxl.setGoalPosition(DXL_ID[i], startArm[i]);
    delay(20);
  }
}

void setHead_Left()
{
      for(int i = 12; i< 14;i++)
  {
    dxl.setGoalPosition(DXL_ID[i],moveHead[i]);
    delay(20);
  }
}

void setHead_Right()
{
      for(int i = 12; i< 14;i++)
  {
    dxl.setGoalPosition(DXL_ID[i],leftHead[i]);
    delay(20);
  }
}

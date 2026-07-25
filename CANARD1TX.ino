#include<Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include<mcp2515.h>
#include<SPI.h>


Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
int ledpin=6;
float threshold=10.00;
bool impact=false;

struct can_frame canMsg;

MCP2515 mcp2515(10);

void setup() {
 Serial.begin(115200);
 accel.begin();
accel.setRange(ADXL345_RANGE_2_G);
pinMode(ledpin,OUTPUT);

  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);  
  mcp2515.setNormalMode();

}

void loop() {
  
sensors_event_t event;
  accel.getEvent(&event);

  float x=event.acceleration.x;
  float y=event.acceleration.y;
  float z=event.acceleration.z;

  float mag =sqrt(x*x+y*y+z*z);


  if(mag>threshold){
    impact=true;
  }

  if(impact==true){
   digitalWrite(ledpin,HIGH);
  }
 

canMsg.can_id  = 0x100;
canMsg.can_dlc = 1;
canMsg.data[0] = impact ? 1 : 0;

mcp2515.sendMessage(&canMsg);

  Serial.println(mag);
  delay(10);

}


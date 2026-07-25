#include<SPI.h>
#include<MFRC522.h>
#include<mcp2515.h>
#define SS_PIN 9
#define RST_PIN 8

MFRC522 myRFID(SS_PIN, RST_PIN); 

struct can_frame  canMsg;
MCP2515 mcp2515(10);
byte authorizedUID[4] = {0x6A, 0x19, 0x19, 0x06};


void setup() {
  Serial.begin(115200);
  SPI.begin();
  myRFID.PCD_Init();
  Serial.println("Please scan your RFID card...");
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);  
  mcp2515.setNormalMode();

}

void loop() 
{
  if ( ! myRFID.PICC_IsNewCardPresent()) 
  {                            
    return;
  }
  if ( ! myRFID.PICC_ReadCardSerial()) 
  {
    return;
  }
  Serial.print("USER ID tag :");
  for (byte i = 0; i < myRFID.uid.size; i++) 
  {
     Serial.print(myRFID.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(myRFID.uid.uidByte[i], HEX);

  }
  delay(1000);
  Serial.println();

canMsg.can_id  = 0x200;
canMsg.can_dlc = 1;

Serial.print("Send Status:");
if (isAuthorized()) {
  canMsg.data[0] = 1;
  MCP2515::ERROR err1 = mcp2515.sendMessage(&canMsg);
  Serial.println(err1);
  delay(3000);
  canMsg.data[0] =2;   
  MCP2515::ERROR err2 = mcp2515.sendMessage(&canMsg);
  Serial.println(err2);

} 
else {
  canMsg.data[0] = 0;
  MCP2515::ERROR err = mcp2515.sendMessage(&canMsg);
  Serial.println(err);
}

delay(100);

}

bool isAuthorized() {
  if (myRFID.uid.size != 4) return false; 
  for (byte i = 0; i < 4; i++) {
    if (myRFID.uid.uidByte[i] != authorizedUID[i]) return false;
  }
  return true;
}

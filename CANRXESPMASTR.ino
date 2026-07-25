#include <U8g2lib.h>
#include <ESP32-TWAI-CAN.hpp>
#include<WiFi.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

#define BLYNK_TEMPLATE_ID "TMPL3ACn-R6pw"
#define BLYNK_TEMPLATE_NAME "CANBUS"
#define BLYNK_AUTH_TOKEN "Cuaw6xv3k5bYr_h-EPLKmFsXAaHfLnIP"

#include <BlynkSimpleEsp32.h>

const int CAN_TX=4;
const int CAN_RX=5;

bool airbagTrig= false;
int  security=0;

void setup() {
  Serial.begin(115200);
  u8g2.begin();

  char auth[] = BLYNK_AUTH_TOKEN;
   char ssid[] = ""; //Write  valid ssid
   char pass[] = ""; //Valid network password

  Blynk.begin(auth,ssid,pass);

  ESP32Can.setPins(CAN_TX, CAN_RX);
  ESP32Can.setSpeed(ESP32Can.convertSpeed(500));  
  ESP32Can.begin();
  

  Blynk.virtualWrite(V0,airbagTrig);
  Blynk.virtualWrite(V1,!security);

  drawScreen();
}

void loop() {

  Blynk.run();

  CanFrame rxFrame;

  if (ESP32Can.readFrame(rxFrame, 100)) {  
    Serial.print("Id: 0x");
    Serial.println(rxFrame.identifier, HEX);
    Serial.print("Data: ");
    Serial.println(rxFrame.data[0]);
  

    switch(rxFrame.identifier){
     case 0x100:
     if (rxFrame.data[0] == 1 && airbagTrig == false) {
         Blynk.logEvent("airbag_open", "Airbag has been activated!");
         }
          airbagTrig = rxFrame.data[0];
        Blynk.virtualWrite(V0,airbagTrig);
      break;

    case 0x200:
     security = rxFrame.data[0];
     if (rxFrame.data[0] == 0) {   
    Blynk.logEvent("unauthorised_attempt", "Unauthorized access attempt detected!");
  }
 
      Blynk.virtualWrite(V1,security==1?0:1);
      break;

      default:
      Serial.print("Unknown ID");
      break;

    }
  }


drawScreen();
}

void drawScreen() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_5x7_tr);

  u8g2.setCursor(2, 30);
  u8g2.print("Airbag Status: ");
  u8g2.print(airbagTrig ? "ON" : "OFF");

  u8g2.setCursor(2, 45);
  u8g2.print("Security Status: ");
  u8g2.print(security==1 ? "OPEN" : "CLOSED");   

  u8g2.sendBuffer();
}

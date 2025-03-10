/**************************************************
 * ESPNowCam video Receiver
 * by @hpsaturn Copyright (C) 2024
 * This file is part ESPNowCam tests project:
 * https://github.com/hpsaturn/ESPNowCam
**************************************************/

#include <Arduino.h>
#include <ESPNowCam.h>
#include "S3_Parallel8_ili9486.h"
#include <LGFX_TFT_eSPI.hpp>
// #include <Utils.h>

ESPNowCam radio;
LGFX tft;

#define LCD_CS 17
#define LCD_BLK 18


// frame buffer
uint8_t *fb; 
// display globals
int32_t dw, dh;

void onDataReady(uint32_t lenght) {
  tft.drawJpg(fb, lenght , 0, 0, dw, dh);
  // printFPS("MF:");
}

void setup() {
  Serial.begin(115200);

  pinMode(LCD_CS, OUTPUT);
  pinMode(LCD_BLK, OUTPUT);

  digitalWrite(LCD_CS, LOW);
  digitalWrite(LCD_BLK, HIGH);

  tft.init();
  tft.setRotation(1);
  tft.startWrite();

  dw = tft.width();
  dh = tft.height();

  if(psramFound()){
    size_t psram_size = esp_spiram_get_size() / 1048576;
    Serial.printf("PSRAM size: %dMb\r\n", psram_size);
  }

  // BE CAREFUL WITH IT, IF JPG LEVEL CHANGES, INCREASE IT
  fb = (uint8_t*)  ps_malloc(5000* sizeof( uint8_t ) ) ;

  radio.setRecvBuffer(fb);
  radio.setRecvCallback(onDataReady);

  if (radio.init()) {
    tft.setTextSize(2);
    tft.drawString("ESPNow Init success", dw / 6, dh / 2);
  }
  delay(1000);
}

void loop() {
}

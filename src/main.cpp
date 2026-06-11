#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#define TFT_CS 10
#define TFT_DC 8
#define TFT_RST 9

Adafruit_ST7735 tft(TFT_CS, TFT_DC, TFT_RST);

void desenharBoneco(int x, int y) {
  tft.fillCircle(x, y, 30, ST7735_MAGENTA);
  tft.fillRect(x-10, y-5, 10, 5, ST7735_BLACK);
  tft.fillRect(x+10, y-5, 10, 5, ST7735_BLACK);
}

void setup() {
  delay(200);
  SPI.begin();
  
  tft.initR(INITR_BLACKTAB);


  tft.fillScreen(ST77XX_WHITE);


  desenharBoneco(60,50);


}
void loop() {
}


#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#define TFT_CS 10
#define TFT_DC 8
#define TFT_RST 9

Adafruit_ST7735 tft(TFT_CS, TFT_DC, TFT_RST);

void desenharBoneco(int x, int y, int largura, int altura) {

  tft.fillCircle(x, y, 32, ST77XX_BLACK);
  tft.fillCircle(x, y, 30, ST7735_MAGENTA);

  tft.fillRect(x-15, y-5, 10, 5, ST7735_BLACK);
  tft.fillRect(x+10, y-5, 10, 5, ST7735_BLACK);

  tft.fillCircle(x - 18, y + 8, 4, ST77XX_RED);
  tft.fillCircle(x + 18, y + 8, 4, ST77XX_RED);

  tft.drawLine(x - 3, y + 12, x + 3, y + 12, ST77XX_BLACK);

  
  tft.drawCircle(x - 35, y + 8, 8, ST77XX_BLACK);
  tft.fillCircle(x - 35, y + 8, 7, ST77XX_MAGENTA);

  tft.drawCircle(x + 35, y + 8, 8, ST77XX_BLACK);
  tft.fillCircle(x + 35, y + 8, 7, ST77XX_MAGENTA);
}

void setup() {
  delay(200);
  SPI.begin();
  
  tft.initR(INITR_BLACKTAB);


  tft.fillScreen(ST77XX_WHITE);


  desenharBoneco(65,70);


}
void loop() {
}


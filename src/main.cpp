#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#define TFT_CS 10
#define TFT_DC 8
#define TFT_RST 9
#define BTN_COMER 2
#define BTN_BRINCAR 3
#define BTN_DORMIR 4

#define BUZZER 5

int fome = 100;
int felicidade = 100;
int energia = 100;

unsigned long ultimoTick = 0;


Adafruit_ST7735 tft(TFT_CS, TFT_DC, TFT_RST);

void desenharBoneco(int x, int y, int largura, int altura) {

  tft.fillRoundRect(
    x - largura/2,
    y - altura/2,
    largura,
    altura,
    altura/2,
    ST77XX_MAGENTA
  );

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


  tft.fillScreen(ST77XX_RED);

  pinMode(BTN_COMER, INPUT_PULLUP);
  pinMode(BTN_BRINCAR, INPUT_PULLUP);
  pinMode(BTN_DORMIR, INPUT_PULLUP);

  pinMode(BUZZER, OUTPUT);

  tft.setTextSize(1);
  tft.setTextWrap(false);

}

void desenharStatus() {

  tft.fillRect(0,0,128,30,ST77XX_WHITE);

  tft.setCursor(2,2);
  tft.setTextColor(ST77XX_BLACK);

  tft.print("Fome:");
  tft.print(fome);

  tft.setCursor(2,12);

  tft.print("Felicidade:");
  tft.print(felicidade);

  tft.setCursor(64,2);

  tft.print("Energia:");
  tft.print(energia);
}


int fomeAntiga = -1;
int felicidadeAntiga = -1;
int energiaAntiga = -1;


void atualizarStatus() {

  if(
    fome != fomeAntiga ||
    felicidade != felicidadeAntiga ||
    energia != energiaAntiga
  ) {

    desenharStatus();

    fomeAntiga = fome;
    felicidadeAntiga = felicidade;
    energiaAntiga = energia;
  }
}

void bip() {
  tone(BUZZER, 1000, 100);
}

boolean frame = true;

unsigned long ultimoFrame = 0;


void loop() {
  atualizarStatus();
  if(millis() - ultimoFrame > 500){

    ultimoFrame = millis();

    frame = !frame;

    tft.fillRect(15,20,100,100,ST77XX_WHITE);

    if(frame)
        desenharBoneco(65,70,50,50);
    else
        desenharBoneco(65,80,60,40);
}
  delay(20);

  if(millis() - ultimoTick > 5000){

    ultimoTick = millis();
  
    fome-2;
  
    felicidade-3;
  
    energia-1;
  
    if(fome < 0) fome = 0;
    if(felicidade < 0) felicidade = 0;
    if(energia < 0) energia = 0;
  }

  if(digitalRead(BTN_COMER) == LOW){

    fome += 10;
  
    if(fome > 100)
      fome = 100;
  
    bip();
  
  }

  if(digitalRead(BTN_BRINCAR) == LOW){

    felicidade += 10;
  
    energia -= 5;
  
    if(felicidade > 100)
      felicidade = 100;
  
    if(energia < 0)
      energia = 0;
  
    bip();
  
  }

  if(digitalRead(BTN_DORMIR) == LOW){

    energia += 20;
  
    if(energia > 100)
      energia = 100;
  
    bip();
  
  }
}


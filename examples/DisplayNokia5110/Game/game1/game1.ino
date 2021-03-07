#include <Eryoma.h>
Eryoma e;

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
int x_player = 35,  x_mob, y_mob, x_bullet, y_bullet = -1;
boolean mobs_create = false;
byte  bullet = 0;
long move_time = 0, move_mob, move_bullet;
int point = 0;
int speed_m = 500;
Adafruit_PCD8544 display = Adafruit_PCD8544(32, 31, 30, 29, 28);
static const unsigned char PROGMEM rocket[] = {
  B00000001, B00000000,
  B00000001, B00000000,
  B00000011, B10000000,
  B00000011, B10000000,
  B00010011, B10010000,
  B00010111, B11010000,
  B00011110, B11110000,
  B00011110, B11110000,
  B00101011, B10101000,
  B00001000, B00100000
};
static const unsigned char PROGMEM _mob[] = {
  B00001000, B00100000,
  B00000100, B01000000,
  B00001111, B11100000,
  B00011011, B10110000,
  B00111111, B11111000,
  B00101111, B11101000,
  B00101000, B00101000,
  B00000111, B11000000
};

static const unsigned char PROGMEM _mob_crush[] = {
  B00100000, B00001000,
  B00010000, B00010000,
  B00111100, B00111000,
  B01101100, B00101100,
  B11111100, B00111110,
  B10111100, B00111010,
  B10100000, B00001010,
  B00011100, B00110000
};

void setup() {
  pinMode(A15, OUTPUT);
  Serial.begin(9600);
  e.setupConnector(4, Keypad);
  randomSeed(analogRead(A8) + analogRead(A9)/2);
  display.drawBitmap(48, x_player, rocket, 16, 10, BLACK);
  display.begin();
  display.clearDisplay();
  display.display();
  display.setContrast(50); // Контраст
}

void loop() {
  // put your main code here, to run repeatedly:
  display.clearDisplay();
  if (millis() - move_mob >= speed_m) mobs();
  if (millis() - move_time >= 30) {
    if (x_player <= 69) {
      if ((e.read(4, 2) == 0) /*&& (x_player != 68)*/) {
        if (bullet == 0) {
          x_player++;
        }
      }
    } else {
      x_player = 0;
    }
    if (x_player >= 0) {
      if ((e.read(4, 0) == 0) /*&& (x_player != 0)*/) {
        if (bullet == 0) {
          x_player--;
        }
      }
    } else {
      x_player = 68;
    }
    move_time = millis();
  }
  if (e.read(4, 1) == 0 && bullet == 0) {

    bullet = 48;
    x_bullet = x_player + 5;
    y_bullet = 38;
    //Serial.println("qwerty");
  }
  if (millis() - move_bullet >= 5 && bullet > 0) {
    y_bullet--;
    move_bullet = millis();
  }

  // Serial.println(x_player);
  if (bullet > 0) {
    display.drawFastVLine(x_bullet + 2, y_bullet, 37 - y_bullet, BLACK);
    bullet--;
    if (bullet == 0) {
      if ((x_bullet + 4 > x_mob + 2) && (x_bullet + 2 < x_mob + 11)) {
        bullet = 0;
        mobs_create = false;
        point++;
        speed_m -=10;
        display.clearDisplay();
        display.setCursor(35, 16);
        display.setTextSize(2);
        display.print(point);
        display.drawBitmap(x_mob, y_mob, _mob_crush, 16, 8, BLACK);
        display.drawBitmap(x_player, 38, rocket, 16, 10, BLACK);
        display.display();
        delay(200);
        mobs();
      }
    }
  }
  if ((bullet > 38-y_mob || bullet == 0) || ((x_bullet + 4 < x_mob + 2) || (x_bullet + 2 > x_mob + 11)))display.drawBitmap(x_mob, y_mob, _mob, 16, 8, BLACK);
    else display.drawBitmap(x_mob, y_mob, _mob_crush, 16, 8, BLACK);
  display.drawBitmap(x_player, 38, rocket, 16, 10, BLACK);
  display.display();
}

/*void loop(){
  display.drawBitmap(0, 0, rocket, 16, 10, BLACK);
  display.drawBitmap(30, 30, _mob, 16, 8, BLACK);
  display.display();
  }*/

void mobs() {
  if (mobs_create == false) {
    x_mob = random(1, 67);
    y_mob = 0;
    mobs_create = true;
  } else {
    y_mob += 2;
    if (y_mob > 38) {
      if (point -10 > 0) {
        display.clearDisplay();
        display.setCursor(30, 8);
        display.setTextSize(1);
        display.print("-10");       
        point -= 10;
        display.setCursor(30, 16);
        display.setTextSize(2);
        display.print(point);
        display.display();
        delay(2000);
      } else {
        display.clearDisplay();
        display.setCursor(18, 8);
        display.setTextSize(2);
        display.print("game");
        display.setCursor(18, 26);
        display.print("over");
        speed_m = 500;
        display.display();
        delay(1000);
        while (e.read(4, 1) == 1){};
        delay(50);
        while (e.read(4, 1) == 0){};
      }
      mobs_create = false;
    }
  }
  move_mob = millis();
}

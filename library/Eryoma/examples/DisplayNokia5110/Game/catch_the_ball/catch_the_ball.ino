#include <Eryoma.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
Eryoma robot;
Adafruit_PCD8544 display = Adafruit_PCD8544(32, 31, 30, 29, 28);

int x_player = 38;

int x_bol = 0;
int y_bol = -2;

int point = 5;
unsigned long time_bol = 0;
boolean _rand = true;

void setup() {
  robot.setupConnector(3, Keypad);
  display.begin();
  display.clearDisplay();
  display.display();
  display.setContrast(50);
  randomSeed(analogRead(A15));
}

static const unsigned char PROGMEM bol[] = {
  B00000000,
  B00000000,
  B00011000,
  B00111100,
  B00111100,
  B00011000,
  B00000000,
  B00000000
};
static const unsigned char PROGMEM platform[] = {
  B11111111
};
void loop() {
  display.clearDisplay();
  display.drawBitmap(x_bol, y_bol, bol, 8, 8, BLACK);
  display.drawBitmap(x_player, 45, platform, 8, 1, BLACK);
  if (_rand) {
    x_bol = random(0, 76);
    _rand = false;
  }
  if (robot.read(3, 0) == 0) {
    x_player--;
  } else {
    if (robot.read(3, 2) == 0) {
      x_player++;
    }
  }
  if ((millis() - time_bol) >= 100) {
    y_bol++;
    if (y_bol >= 41) {
      if ((x_bol - x_player < 6) && (x_bol - x_player > -6)) {
        _rand = true;
        y_bol = -3;
        point++;
      }else{
        point--;
        _rand = true;
        y_bol = -3;
      }
    }
    time_bol = millis();
  }
  display.display();
}

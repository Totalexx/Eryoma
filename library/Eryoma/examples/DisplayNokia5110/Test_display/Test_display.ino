#include <Eryoma.h>
Eryoma robot;
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(32, 31, 30, 29, 28);
void setup() {
  display.begin();
  display.clearDisplay();
  display.display();
  display.setContrast(50);
}

static const unsigned char PROGMEM test[] = {
  B00000000,
  B00011000,
  B00111100,
  B01111110,
  B01111110,
  B00111100,
  B00011000,
  B00000000
  };

void loop() {
  display.clearDisplay();
  display.print("hello");
  display.drawBitmap(84/2, 48/2, test, 8, 8, BLACK);
  display.display();
}


#include <Eryoma.h> // Подключаем библиотеку
Eryoma robot; 

void setup() {
  robot.setupConnector(1, Keypad); // Указываем, что на 1 коннекторе подключён KeyPad
  Serial.begin(115200); // Устанавливаем скорость COM порта 
}

void loop() {
  Serial.println(robot.read(1, 0)); // Считываем значения 1 кнопки (1 - не нажато, 0 - нажато)
  Serial.println(robot.read(1, 1)); // Считываем значения 2 кнопки (1 - не нажато, 0 - нажато)
  Serial.println(robot.read(1, 2)); // Считываем значения 3 кнопки (1 - не нажато, 0 - нажато)
  Serial.println(robot.read(1, 3)); // Считываем значения с потенциометра 
  Serial.println();
  delay(20); // Ждём 20 мс
}

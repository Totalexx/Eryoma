#include <Eryoma.h> // Подключаем библиотеку
Eryoma robot; // Создаём экземпляр класса Eryoma 

void setup() {
  robot.setupConnector(1, Keypad); // Указываем, что на 1 коннекторе подключён KeyPad
  Serial.begin(115200); // Устанавливаем скорость COM-порта 
}

void loop() {
  Serial.println(robot.read(1, 0)); // Считываем значения первой кнопки (1 - не нажато, 0 - нажато)
  Serial.println(robot.read(1, 1)); // Считываем значения второй кнопки (1 - не нажато, 0 - нажато)
  Serial.println(robot.read(1, 2)); // Считываем значения третий кнопки (1 - не нажато, 0 - нажато)
  Serial.println(robot.read(1, 3)); // Считываем значения с потенциометра 
  Serial.println();
  delay(100); // Ждём 100 мс
}

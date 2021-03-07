#include <Eryoma.h> // Подключаем библиотеку
Eryoma robot; // Создаём экземпляр класса Eryoma

void setup() {
  robot.setupConnector(1, Ultrasonic); // Указываем, что на 1 коннекторе подключён Ultrasonic
  Serial.begin(115200); // Устанавливаем скорость COM-порта 115200 Бод 
}

void loop() {
  Serial.println(robot.read(1)); // Считываем значения расстояния(в см) с 1 коннектора
  delay(100); // Задержка 100 мс
}

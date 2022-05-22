#include <Eryoma.h> // Подключаем библиотеку
Eryoma robot; // Создаём экземпляр класса Eryoma 

void setup() {
  robot.setupConnector(1, TrafficLight); // Указываем, что на 1 коннекторе подключён TrafficLight
  Serial.begin(115200); // Устанавливаем скорость COM-порта 115200 Бод
}

void loop() {
  Serial.println(robot.read(1)); // Считываем значения c фоторезистора с 1 коннектора и выводим в COM-порт
  delay(200); // Задержка 200 мс
}

#include <Eryoma.h> // Подключаем библиотеку
Eryoma robot; // Создаём экземпляр класса Eryoma

void setup() {
  robot.setupConnector(1, LineArray); // Указываем, что на первом коннекторе подключён LineSensor
  Serial.begin(115200); // Устанавливаем скорость COM-порта
}

void loop() {
  Serial.print(robot.read(1, 0)); // Считываем значения c 0 датчика LineArray с первого коннектора и выводим в COM-порт
  Serial.print(" "); // Выводим пробел в COM-порт для разделения значений
  Serial.print(robot.read(1, 1)); // Считываем значения c 1 датчика LineArray с первого коннектора и выводим в COM-порт
  Serial.print(" "); 
  Serial.print(robot.read(1, 2)); // Считываем значения c 2 датчика LineArray с первого коннектора и выводим в COM-порт
  Serial.print(" "); 
  Serial.print(robot.read(1, 3)); // Считываем значения c 3 датчика LineArray с первого коннектора и выводим в COM-порт
  Serial.print(" "); 
  Serial.print(robot.read(1, 4)); // Считываем значения c 4 датчика LineArray с первого коннектора и выводим в COM-порт
  Serial.print(" "); 
  Serial.print(robot.read(1, 5)); // Считываем значения c 5 датчика LineArray с первого коннектора и выводим в COM-порт
  Serial.print(" "); 
  Serial.print(robot.read(1, 6)); // Считываем значения c 6 датчика LineArray с первого коннектора и выводим в COM-порт
  Serial.print(" "); 
  Serial.println(robot.read(1, 7)); // Считываем значения c 7 датчика LineArray с первого коннектора и выводим в COM-порт
  delay(20);
}

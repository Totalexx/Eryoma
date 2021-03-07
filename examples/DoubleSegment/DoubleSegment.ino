#include <Eryoma.h> // Подключаем библиотеку
Eryoma robot; // Создаём экземпляр класса Eryoma

void setup() {
  robot.setupConnector(1, DoubleSegment); // Указываем, что на 1 коннекторе подключён DoubleSegment
}

void loop() {
  robot.write(1, 88); // Выводим число 88 на индекатор, где 1 - номер коннектора
  delay(1000); //Ожидание 1 секунд 
  robot.write(1, 8.8); // Выводим число 8.8 на индекатор, где 1 - номер коннектора
  delay(1000); //Ожидание 1 секунд
}

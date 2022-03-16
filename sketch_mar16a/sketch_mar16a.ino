#include <VL53L0X.h>  
#include <Wire.h>     

#define XSHUT_TOF_1  10
#define XSHUT_TOF_2  11
#define XSHUT_TOF_3  12

#define TOF_1_ADDR  0x2A
#define TOF_2_ADDR  0x2B
#define TOF_3_ADDR  0x2C

VL53L0X tof_1;
VL53L0X tof_2;
VL53L0X tof_3;


void setup() { 
  Serial.begin(9600);
  while (!Serial) {
    ; // ожидаем подключения монитора порта
  }
         
  // деактивируем оба модуля, чтобы избежать конфликтов адрессации
  pinMode(XSHUT_TOF_1, OUTPUT);
  pinMode(XSHUT_TOF_2, OUTPUT);
  pinMode(XSHUT_TOF_3, OUTPUT);

  Wire.begin();   // активируем интерфейс I2C, arduino будем мастером

  // назначаем адрес первому модулю, активируем его и ожидаем выхода на нормальный режим работы
  pinMode(XSHUT_TOF_1, INPUT);
  delay(10);
  tof_1.setAddress(TOF_1_ADDR);
  
  

 // назначаем адрес второму модулю, активируем его и ожидаем выхода на нормальный режим работы
  pinMode(XSHUT_TOF_2, INPUT);
  delay(10);
  tof_2.setAddress(TOF_2_ADDR);

  pinMode(XSHUT_TOF_3, INPUT);
  delay(10);
  tof_3.setAddress(TOF_3_ADDR);
  
   
  // задаем таймаут ожидания данных для каждого модуля
  tof_1.setTimeout(1000);
  tof_2.setTimeout(1000);
  tof_3.setTimeout(1000);

  // инициализируем модули
  if (tof_1.init() == 0) {
    Serial.println("Не удалось обнаружить и инициализировать датчик 1!");
    while (1) {}
  }

  if (tof_2.init() == 0) {
   Serial.println("Не удалось обнаружить и инициализировать датчик 2!");
   while (1) {}
   }

   if (tof_3.init() == 0) {
   Serial.println("Не удалось обнаружить и инициализировать датчик 2!");
   while (1) {}
   }

  // запускаем модули в continuius режиме измерений
  tof_1.startContinuous();
  tof_2.startContinuous();
  tof_3.startContinuous();
}

int distance_1 = 0;
int distance_2 = 0;
int distance_3 = 0;

void loop() {
  distance_1 = tof_1.readRangeContinuousMillimeters();
  if (tof_1.timeoutOccurred()) { 
    Serial.println(" ТАЙМАУТ"); 
  }

  distance_2 = tof_2.readRangeContinuousMillimeters();
  if (tof_2.timeoutOccurred()) { 
    Serial.println(" ТАЙМАУТ"); 
  }

  distance_3 = tof_3.readRangeContinuousMillimeters();
  if (tof_3.timeoutOccurred()) { 
    Serial.println(" ТАЙМАУТ"); 
  }
  
 Serial.println("TOF1 = " + String(distance_1) + "   TOF2 = " + String(distance_2) + "   TOF3 = " + String(distance_3));
}

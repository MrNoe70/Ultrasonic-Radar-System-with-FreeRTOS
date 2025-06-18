#include <LiquidCrystal_I2C.h>
#include <Arduino_FreeRTOS.h>
#include <Servo.h>
#include <semphr.h>

#define TRIGGER 1
#define ECHO 2

LiquidCrystal_I2C lcd(0x27, 16, 2);

SemaphoreHandle_t deviceSem;

//servo related
Servo servo;
int angle = 90;
boolean counterClockwise;
boolean objectDetected; //for printing to LED

//radar related
long totalTime;
double distance; //in cm
boolean canDetect = true;
double detectedDistance;

void setup() {
  //init tasks
  xTaskCreate(LCDTask, "LCDTask", 128, NULL, 3, NULL);
  xTaskCreate(ServoTask, "ServoTask", 128, NULL, 2, NULL);
  xTaskCreate(RadarTask, "RadarTask", 128, NULL, 1, NULL);

  //init semaphore
  deviceSem = xSemaphoreCreateBinary();
  xSemaphoreGive(deviceSem);

  //start lcd 
  lcd.init();
  lcd.backlight();

  //start servo
  servo.attach(0);
  setAngle(0);

  //start radar
  pinMode(TRIGGER, OUTPUT); //for trigger
  pinMode(ECHO, INPUT); //for echo
}

void ServoTask(void *pvParameters) {
  while(1) {
    if (xSemaphoreTake(deviceSem, portMAX_DELAY) == pdTRUE) {
      if (counterClockwise) {
        setAngle(++angle);
        if (angle >= 180) counterClockwise = false;
      }
      else {
        setAngle(--angle);
        if (angle <= 0) counterClockwise = true;
      }
      xSemaphoreGive(deviceSem);
      vTaskDelay(1);
    }
  }
}

void RadarTask(void *pvParameters) {
  while(1) {
    if (xSemaphoreTake(deviceSem, portMAX_DELAY) == pdTRUE) {
      digitalWrite(TRIGGER, LOW);
      delayMicroseconds(2);

      digitalWrite(TRIGGER, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIGGER, LOW);

      //get distance
      totalTime = pulseIn(ECHO, HIGH);
      distance = totalTime * 0.035 / 2;

      //upon detection, which is defined by distance <= 20, stop rotation
      //and afterwards pause detecting
      if (distance <= 20 && canDetect) {
        objectDetected = true;
        detectedDistance = distance;
        vTaskDelay(20);
        objectDetected = false;
        canDetect = false;
      }
      canDetect = true;

      xSemaphoreGive(deviceSem);
      vTaskDelay(20);
    }
  }
}

void LCDTask(void *pvParameters) {
  while(1) {
    if (objectDetected) {
      lcd.setCursor(0, 0);
      lcd.print("Dist: ");
      lcd.print(detectedDistance);
      lcd.print("    ");
    }
    else {
      lcd.setCursor(0, 0);
      lcd.print("Dist: ");
      lcd.print("n/a");
      lcd.print("    ");
    }

    //print angle info to lcd
    lcd.setCursor(0, 1);
    lcd.print("Angle: ");
    lcd.print(angle);
    lcd.print("    ");

    vTaskDelay(1);
  }
}

void loop() {}

void setAngle(int value) {
  angle = value;
  servo.write(value);
}

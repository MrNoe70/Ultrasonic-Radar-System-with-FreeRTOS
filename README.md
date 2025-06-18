# Ultrasonic Radar System with FreeRTOS on Arduino Uno

## Abstract
This project presents the design and implementation of an ultrasonic radar system using the Arduino Uno microcontroller and FreeRTOS. The system employs an HC-SR04 ultrasonic sensor mounted on a servo motor to scan a 180° field and detect objects based on their distance. Upon detecting an object within 20 cm, the system pauses rotation and displays the detected angle and distance on a 16x2 I2C LCD. The implementation leverages FreeRTOS to manage concurrent tasks for servo control, sensor data acquisition, and display updates. Inter-task communication and resource synchronization are handled using binary semaphores, ensuring efficient and reliable operation. This project demonstrates how real-time operating systems can enhance the performance of embedded systems by enabling modular, scalable, and responsive designs.

## Index Terms
Ultrasonic Radar, FreeRTOS, Arduino Uno, HC-SR04, Servo Motor, Real-Time Systems, Multitasking, Embedded Systems

## Hardware Components
- **Arduino Uno**: The central processing unit, running FreeRTOS and executing the project's tasks.
- **Ultrasonic Sensor (HC-SR04)**: Measures the distance to objects using sound waves.
- **Servo Motor (SG90)**: Rotates the ultrasonic sensor to scan the environment.
- **16x2 I2C LCD**: Displays the system's output, specifically the detected distance and the current angle of the sensor.
- **Breadboard and Jumpers**: Used for circuit connections.

### Wiring Diagram
- **Ultrasonic Sensor (HC-SR04)**:
  - VCC to Arduino 5V
  - GND to Arduino GND
  - Trigger (TRIG) pin to Arduino Digital Pin 1
  - ECHO pin to Arduino Digital Pin 2

- **Servo Motor (SG90)**:
  - VCC to Arduino 5V
  - GND to Arduino GND
  - Signal to Arduino Digital Pin 0

- **16x2 I2C LCD**:
  - VCC to Arduino 5V
  - GND to Arduino GND
  - SDA to Arduino SDA pin (A4)
  - SCL to Arduino SCL pin (A5)

## Software Tools
- Arduino IDE
- FreeRTOS (Arduino version)
- Servo, LiquidCrystal I2C libraries

## Functional Overview
- **ServoTask**: Rotates the servo between 0-180°.
- **RadarTask**: Triggers the ultrasonic sensor and calculates distance.
- **LCDTask**: Displays the angle and detected object distance.
- **Binary Semaphore**: Ensures safe hardware access among tasks.

## Results and Discussion
Upon powering the system:
1. The Arduino initializes FreeRTOS, creates the three tasks, and starts the scheduler.
2. The servo motor begins its sweep from 0 to 180 degrees and back.
3. The ultrasonic sensor continuously takes distance readings at the current angle of the servo.
4. The LCD updates to show the current angle and "Dist: n/a".

When an object is placed within approximately 20 cm of the ultrasonic sensor:
- The `RadarTask` detects it, sets the `objectDetected` flag, captures the distance, and pauses further detection for a short period.
- The `LCDTask` reads the `objectDetected` flag and displays the captured distance along with the angle at which the object was detected.
- Once the pause in the `RadarTask` is over, detection is re-enabled.

### Photos
1. **Project Wiring on Breadboard**  
   ![image](https://github.com/user-attachments/assets/b234b6a8-3d92-460c-8164-65f7b821d14f)
   
3. **System at Idle with No Object**  
   ![image](https://github.com/user-attachments/assets/3d8714fa-c8d6-46e2-9019-9709340228c4)
   
5. **System Detecting an Object**  
  ![image](https://github.com/user-attachments/assets/f21a1201-45e8-4192-9734-66260b4a81b3)


6. **Servo and Ultrasonic Sensor Pointing at Object**  
   ![image](https://github.com/user-attachments/assets/2047489a-8022-4529-9135-972900f1b9d7)



## Conclusion
This project successfully implemented a basic ultrasonic radar system utilizing the multitasking capabilities of FreeRTOS on an Arduino microcontroller. By dividing the system's functionality into dedicated tasks for servo control, ultrasonic sensing, and LCD display, the project achieved concurrent operation and improved system responsiveness. The use of a semaphore effectively managed access to shared resources, ensuring the integrity of data passed between tasks. The system is capable of scanning a 180-degree area, detecting objects within a 20 cm range, and displaying the detected distance and angle on an LCD. This project serves as a practical demonstration of applying FreeRTOS principles to build real-time embedded systems.

## References
1. SparkFun Electronics. (n.d.). HC-SR04 ultrasonic sensor datasheet. [Link](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf)
2. Barry, R. (n.d.). FreeRTOS: The real-time operating system for microcontrollers. [Link](https://www.freertos.org/)
3. Arduino. (n.d.). Servo library. [Link](https://www.arduino.cc/en/reference/servo)
4. TowerPro. (n.d.). SG90 9g micro servo motor datasheet. [Link](https://www.friendlywire.com/projects/ne555-servo-safe/SG90-datasheet.pdf)
5. Rickman, J. (n.d.). LiquidCrystal I2C library for Arduino. [Link](https://github.com/johnrickman/LiquidCrystal_I2C)

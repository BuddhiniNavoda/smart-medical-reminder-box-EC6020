# smart-medical-reminder-box-EC6020
## 👩‍💻 Team Members

- 2021/E/008 (https://github.com/DinushDilhan)
- 2021/E/062 (https://github.com/BuddhiniNavoda)
- 2021/E/110 (https://github.com/KanchanaAriyasinghe)
- 2021/E/135 (https://github.com/JudeFernando01)
- 2021/E/136 (https://github.com/ChamidukaUdathari)

##  Introduction
The Smart Medicine Reminder Box is an innovative embedded system designed to ensure patients take their medication on time. By combining hardware and software components, the system provides an efficient way to schedule medicine times, alert patients, making healthcare management simpler and safer.

##  Purpose
This project addresses the problem of missed or incorrect medication intake by:
- Allowing users to set, edit, or delete medicine schedules via a mobile app.
- Providing real-time alerts and notifications to patients when it's time to take their medicine.
- Detecting and logging whether the medicine box is opened or closed.
  - Sending alerts to the mobile app if the box is opened before the scheduled time and after taking the medicine
  - Displaying the current time and counting down to the next schedule on the LED's screen.

##  Features
1. **Mobile Application**:
   - Add, delete, and update medication schedules.
   - Receive alerts for upcoming medications and when the box opens or closes.

2. **Embedded System**:
   - Real-time clock (RTC) for precise schedule tracking.
   - LED display for showing current time and medicine schedule.
   - Servo motor for opening and closing the box after a few minutes.
   - Magnetic sensor to identify box is open or closed.
3. **Cloud Integration**:
   - Synchronization of schedules between mobile app and hardware using Firebase.

##  Architecture
The system is designed using a high-level architecture that ensures seamless communication between all components:
1. **Hardware Components**: 
   - ESP32 microcontroller
   - RTC module
   - LED display
   - Servo motor
   - Magnetic sensor
2. **Software**:
   - Mobile app (for scheduling and alerts)
   - Firebase (for data storage and real-time sync)
3. **Communication Protocols**:
   - I2C for OLED and RTC modules
   - MQTT/HTTP for mobile app and ESP32 communication
## Solution Architecture

## Flow Chart

## Block Diagram

## Hardware Design


## Detailed budget

## Advising Lecturers
  - Mrs. Mary Regin Kamalina
  - Mr. Nishankar Sathiyamohan

###
  - This will not be the end! Thank you!
  

   


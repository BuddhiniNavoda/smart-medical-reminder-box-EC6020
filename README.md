# smart-medical-reminder-box-EC6020
## 👩‍💻 Team Members

- 2021/E/008 (https://github.com/DinushDilhan)
- 2021/E/062 (https://github.com/BuddhiniNavoda)
- 2021/E/110 (https://github.com/KanchanaAriyasinghe)
- 2021/E/135 (https://github.com/JudeFernando01)
- 2021/E/136 (https://github.com/ChamidukaUdathari)

##  Introduction
The Smart Medicine Reminder Box is an innovative embedded system designed to ensure patients take their medication on time. By combining hardware and software components, the system provides an efficient way to schedule medicine times, and alert patients, making healthcare management simpler and safer.

##  Purpose
This project addresses the problem of missed or incorrect medication intake by:
- Allowing users to set, edit, or delete medicine schedules via a mobile app.
- Providing real-time alerts and notifications to patients when it's time to take their medicine.
- Detecting and logging whether the medicine box is opened or closed.
  - Display the message  if the box is opened before the scheduled time and after taking the medicine
  if the box is opened before the scheduled time and after taking the medicine
  - Displaying the current time and counting down to the next schedule on the LED's screen.

##  Features
1. **web Application**:
  
   - Add, delete, and update medication schedules.
  
   - Web Application Repo. link : [MediReminder Web Application Repo.](https://github.com/BuddhiniNavoda/MedReminder_EC6020.git)
  
   - Web App link : [MediReminder](https://med-reminder-ec-6020.vercel.app/)
  
     ![web app](https://github.com/BuddhiniNavoda/smart-medical-reminder-box-EC6020/blob/main/Design/mediapp.png?raw=true)

3. **Embedded System**:
   - Real-time clock (RTC) for precise schedule tracking.
   - LED display for showing current time and medicine schedule.
   - Servo motor for opening and closing the box after a few minutes.
   - Magnetic sensor to identify box is open or closed.
4. **Cloud Integration**:
   - Synchronization of schedules between web app and hardware using Firebase.

##  Architecture
The system is designed using a high-level architecture that ensures seamless communication between all components:

  ![architecture](https://github.com/BuddhiniNavoda/smart-medical-reminder-box-EC6020/blob/main/Block_Diagram/Architechture_new.png?raw=true)
1. **Hardware Components**: 
   - ESP32 microcontroller
   - RTC module
   - LED display
   - Servo motor
   - Magnetic sensor
2. **Software**:
   - Web app (for scheduling and alerts)
   - Firebase (for data storage and real-time sync)
3. **Communication Protocols**:
   - I2C for OLED and RTC modules
   - MQTT/HTTP for web app and ESP32 communication
     
## Flow Chart
  ![flow chart](https://github.com/BuddhiniNavoda/smart-medical-reminder-box-EC6020/blob/main/Flow_Chart/flow%20chart.PNG?raw=true)

## Block Diagram
  ![block diagram](https://github.com/BuddhiniNavoda/smart-medical-reminder-box-EC6020/blob/main/Block_Diagram/Block%20diagram_1.jpg?raw=true)


## Prototype Design


  💡  **Design link** : [Prototype design file ](https://wokwi.com/projects/421039257316816897)


  
  ![Prototype Design](https://github.com/BuddhiniNavoda/smart-medical-reminder-box-EC6020/blob/main/Design/prototype%20design_1.jpg?raw=true
)
## Final Product
![medibox](https://github.com/BuddhiniNavoda/smart-medical-reminder-box-EC6020/blob/main/Design/medibox.jpg?raw=true
)

![medibox2](https://github.com/BuddhiniNavoda/smart-medical-reminder-box-EC6020/blob/main/Design/medibox2.jpg?raw=true)

## Detailed budget
  ![budget](https://github.com/BuddhiniNavoda/smart-medical-reminder-box-EC6020/blob/main/Project_Proposal/buget_1.jpg?raw=true)


## Advising Lecturers
  - Mrs. Mary Regin Kamalina
  - Mr. Nishankar Sathiyamohan


  

   


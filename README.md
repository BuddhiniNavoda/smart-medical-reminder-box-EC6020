# smart-medical-reminder-box-EC6020
## 👩‍💻 Team Members

- 2021/E/008 (https://github.com/DinushDilhan)
- 2021/E/062 (https://github.com/BuddhiniNavoda)
- 2021/E/110 (https://github.com/KanchanaAriyasinghe)
- 2021/E/135 (https://github.com/JudeFernando01)
- 2021/E/136 (https://github.com/ChamidukaUdathari)

## 📖 Introduction
The Smart Medicine Reminder Box is an innovative embedded system designed to ensure patients take their medication on time. By combining hardware and software components, the system provides an efficient way to schedule medicine times, alert patients, making healthcare management simpler and safer.

## 🎯 Purpose
This project addresses the problem of missed or incorrect medication intake by:
- Allowing users to set, edit, or delete medicine schedules via a mobile app.
- Providing real-time alerts and notifications to patients when it's time to take their medicine.
- Detecting and logging whether the medicine box is opened or closed.
  - Sending alerts to the mobile app if the box is opened before the scheduled time and after takeing the medicine
  - Displaying the current time and counting down to the next schedule on the LED's screen.

## ⚙️ Features
1. **Mobile Application**:
   - Add, delete, and update medication schedules.
   - Receive alerts for upcoming medications and when box opened or closed.

2. **Embedded System**:
   - Real-time clock (RTC) for precise schedule tracking.
   - LED display for showing current time and medicine schedule.
   - Servo motor for open and closed the box after few minutes.
   - Magnetic sensor to identify box open or close.
3. **Cloud Integration**:
   - Synchronization of schedules between mobile app and hardware using Firebase.
   


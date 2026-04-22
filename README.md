# 🔥 LPG Gas Detection System using Arduino

## Overview

Leakage of LPG gas is a major safety concern in households and industries, often leading to fire hazards and explosions. This project focuses on designing a **low-cost, real-time LPG gas detection system** using Arduino that alerts users immediately when gas concentration exceeds safe levels.

## Objective

* Detect LPG gas leakage in real-time
* Provide instant alert using buzzer and LED
* Develop a reliable and cost-effective safety system

##  Working Principle

The system uses an **MQ-2 gas sensor**, which is sensitive to LPG, propane, methane, and smoke.

* The sensor detects gas concentration in the air
* It changes its internal resistance based on gas levels
* This change is converted into an analog voltage signal
* The Arduino reads this value and compares it with a predefined threshold
* If the threshold is exceeded:

  * 🔴 LED turns ON
  * 🔊 Buzzer activates

## Components Used

* Arduino Uno
* MQ-2 Gas Sensor
* Buzzer
* LED
* Resistors
* Breadboard
* Jumper wires

## Circuit Diagram

<img width="742" height="518" alt="image" src="https://github.com/user-attachments/assets/59a512fc-2bee-4247-bbba-a1df7588bde9" />
A detailed circuit schematic is under development. The system is currently implemented and tested using a breadboard-based connection.


## Code Explanation

The Arduino continuously reads analog data from the MQ-2 sensor:

* `analogRead()` is used to capture gas levels
* A threshold value is defined based on calibration
* Conditional logic (`if-else`) triggers alert mechanisms

---

## Results

* Successfully detects LPG gas presence
* Provides immediate audio-visual alert
* Demonstrated using real-time testing

Images and video demonstration are included in this repository.

## Challenges Faced

* Sensor calibration for accurate detection
* Avoiding false triggering due to environmental factors
* Sensitivity adjustment for different gas concentrations

## Future Improvements

*  IoT integration for mobile alerts
*  GSM module for SMS notification
*  Automatic exhaust fan activation
*  Gas concentration monitoring dashboard

##  Conclusion

This project demonstrates a practical and affordable solution for gas leakage detection. It highlights the importance of embedded systems in improving **safety and real-world problem solving**.
---

## ⭐ Note

This project is developed for learning and demonstration purposes. It can be further enhanced for real-world industrial applications.

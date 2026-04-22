## ⚙️ Working of the System

The LPG Gas Detection System operates in real-time using an MQ-2 gas sensor connected to an Arduino Uno. The system continuously monitors the surrounding air for the presence of LPG gas and triggers alerts when unsafe levels are detected.

### Step-by-Step Working:

1. **Sensor Initialization**
   The MQ-2 gas sensor is powered and allowed to warm up for stable readings. During this time, it starts sensing the surrounding air.

2. **Gas Detection**
   The sensor continuously detects the concentration of LPG and other combustible gases in the environment and generates an analog voltage signal based on gas intensity.

3. **Signal Processing**
   The Arduino Uno reads the analog output from the MQ-2 sensor using its analog input pin. This value represents the gas concentration level.

4. **Threshold Comparison**
   The received sensor value is compared with a predefined threshold value set in the program. This threshold is determined based on testing in a normal environment.

5. **Decision Making**
   - If the sensor value is **below the threshold**, the system remains in a normal state and no alert is triggered.
   - If the sensor value **exceeds the threshold**, the system detects it as a potential gas leakage condition.

6. **Alert Activation**
   When gas leakage is detected:
   - The LED turns ON as a visual warning
   - The buzzer is activated as an audible alert

7. **Continuous Monitoring**
   The system runs in a continuous loop, ensuring real-time monitoring of gas levels at all times.

### System Flow:
LPG Gas in Environment → MQ-2 Sensor → Arduino Uno → Threshold Check → LED + Buzzer Alert

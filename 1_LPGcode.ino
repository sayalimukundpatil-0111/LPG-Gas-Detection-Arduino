/*
  MQ-6 Gas Detection -> Fan (MOSFET), Buzzer, Servo
  - MQ-6 AO -> A0
  - MOSFET Gate -> D10 (with ~220Ω gate resistor), MOSFET Source -> GND, Drain -> Motor negative
  - Buzzer + -> D8, Buzzer - -> GND
  - Servo signal -> D9, Servo VCC -> 5V, Servo GND -> GND
  - Common GND for Arduino and motor supply (if external)
  
  Behavior:
  - Uses a 10-sample moving average to stabilize sensor readings.
  - Hysteresis: 'onThreshold' to turn devices ON, 'offThreshold' to turn them OFF.
  - Warm-up period after startup for sensor stabilization.
*/

#include <Servo.h>

const int mqPin = A0;        // MQ-6 analog output
const int motorPin = 10;     // MOSFET gate (drives fan/motor)
const int buzzerPin = 8;     // Buzzer control pin
const int servoPin = 9;      // Servo signal pin

// Tuning parameters (adjust after testing)
const int onThreshold  = 200; // if averaged reading >= onThreshold -> gas detected
const int offThreshold = 150; // if averaged reading <= offThreshold -> gas cleared (hysteresis)
const int samples = 10;       // moving average samples
const unsigned long serialInterval = 1000; // ms between serial reports
const unsigned long warmupDelay = 30000;   // ms warm-up (30s) - increase if needed

// Servo positions
const int servoSafePos = 90;  // servo angle when gas detected
const int servoIdlePos = 0;   // servo angle when no gas

Servo safetyServo;
int readings[samples];
int readIndex = 0;
long total = 0;
int average = 0;

unsigned long lastSerialTime = 0;
bool gasState = false; // current state (true = detected)

void setup() {
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(motorPin, LOW);
  digitalWrite(buzzerPin, LOW);

  // initialize moving average buffer
  for (int i = 0; i < samples; i++) {
    readings[i] = analogRead(mqPin);
    delay(20);
  }
  total = 0;
  for (int i = 0; i < samples; i++) total += readings[i];
  average = total / samples;

  // attach servo
  safetyServo.attach(servoPin);
  safetyServo.write(servoIdlePos);

  Serial.println("MQ-6 Gas Detection System starting...");
  Serial.print("Warm-up for ");
  Serial.print(warmupDelay / 1000);
  Serial.println(" seconds. Please wait...");
  delay(warmupDelay);
  Serial.println("Warm-up complete. Monitoring started.");
  lastSerialTime = millis();
}

void loop() {
  // read sensor and update moving average
  int sensorVal = analogRead(mqPin);

  // update circular buffer
  total -= readings[readIndex];
  readings[readIndex] = sensorVal;
  total += readings[readIndex];
  readIndex = (readIndex + 1) % samples;
  average = total / samples;

  // hysteresis logic
  if (!gasState && average >= onThreshold) {
    gasState = true;
    activateSafety();
  } else if (gasState && average <= offThreshold) {
    gasState = false;
    deactivateSafety();
  }

  // periodic serial output
  unsigned long now = millis();
  if (now - lastSerialTime >= serialInterval) {
    Serial.print("Avg: ");
    Serial.print(average);
    Serial.print("  Raw: ");
    Serial.print(sensorVal);
    Serial.print("  State: ");
    Serial.println(gasState ? "GAS DETECTED" : "No Gas");
    lastSerialTime = now;
  }

  delay(100); // small delay to limit read rate
}

void activateSafety() {
  // Turn motor ON (drive MOSFET gate HIGH)
  digitalWrite(motorPin, HIGH);

  // Activate buzzer (continuous)
  digitalWrite(buzzerPin, HIGH);

  // Move servo to safety position
  safetyServo.write(servoSafePos);

  // Optional: short debug print
  Serial.println(">>> GAS DETECTED -> Motor ON, Buzzer ON, Servo to safe position");
}

void deactivateSafety() {
  // Turn motor OFF
  digitalWrite(motorPin, LOW);

  // Turn buzzer OFF
  digitalWrite(buzzerPin, LOW);

  // Move servo back to idle
  safetyServo.write(servoIdlePos);

  Serial.println(">>> Gas cleared -> Motor OFF, Buzzer OFF, Servo to idle");
}
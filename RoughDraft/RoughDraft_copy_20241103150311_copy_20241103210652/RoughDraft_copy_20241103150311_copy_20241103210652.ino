// Includes the Arduino Stepper Library
#include <Stepper.h>

// Variables for the Pulse Sensor
int PulseSensorPurplePin = 0;  // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int Signal;                    // Holds the incoming raw data from the Pulse Sensor
int Threshold = 600;           // Threshold to detect a heartbeat
int lastSignal = 0;            // To store the previous signal value
bool moveDirection = true;     // Flag to alternate direction

// Stepper motor setup
const int stepsPerRevolution = 1500;  // Number of steps per full rotation for your motor
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);  // Pins for the stepper motor

void setup() {
  Serial.begin(115200);        // Sets up Serial Communication at 115200 baud rate
  myStepper.setSpeed(20);      // Set the speed of the stepper motor (20 RPM)
}

void loop() {
  Signal = analogRead(PulseSensorPurplePin);  // Read the Pulse Sensor's value

  Serial.println("Signal " + String(Signal)); // Print the signal to the Serial Monitor (optional for debugging)

  // Detect heartbeat only on the rising edge (when the signal crosses the threshold upward)
  if (Signal > Threshold && lastSignal < Threshold) {  
    // Move in one direction if moveDirection is true, otherwise move in the opposite direction
    if (moveDirection) {
      myStepper.step(stepsPerRevolution / 8);  // Move 1/8th of a revolution in one direction
    } else {
      myStepper.step(-stepsPerRevolution / 8); // Move 1/8th of a revolution in the opposite direction
    }

    moveDirection = !moveDirection;  // Toggle the direction for the next heartbeat
    delay(200);  // Small delay to avoid multiple triggers for one heartbeat
  }

  // Store the current signal as the last signal for the next loop iteration
  lastSignal = Signal;

  delay(20); 
}

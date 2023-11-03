#include <Wire.h>
#include "MQ135.h"
#include <SoftwareSerial.h>

SoftwareSerial bluetoothSerial(3, 1); // Define SoftwareSerial pins (RX, TX) for HC-05

const int mqPin = A0; // Analog pin connected to MQ135 sensor
MQ135 gasSensor = MQ135(mqPin);

const int gasThreshold = 1000; // Threshold for gas concentration in ppm

void setup() {


  Serial.begin(115200);         // Serial monitor for debugging
  bluetoothSerial.begin(9600);  // Bluetooth module baud rate
}

void loop() {
  // Read the analog value from the MQ135 sensor
  
  // Convert the analog value to a gas concentration (you may need to calibrate this)
  float gasConcentration = gasSensor.getPPM();
  

  // Send only the gas concentration over Bluetooth as a single line
  bluetoothSerial.print(gasConcentration, 2);// Send the gas concentration with 2 decimal places
  bluetoothSerial.println(" ppm");



  // Check if gas concentration exceeds the threshold
  if (gasConcentration > gasThreshold) {
    // Notify the user through Bluetooth
    bluetoothSerial.println("WARNING: High Gas Concentration Detected!");
  }

  delay(1700); // Update the display and send data every second (adjust as needed)
}

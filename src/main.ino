#include <Servo.h>

Servo continuousServo;

// Determine general properties
const int servoPin = 8;
const int servoSpeed = 3;

// Map the servo speed value to a .writeMicroseconds() unit
const int mappedServoSpeed = map(servoSpeed, -50, 50, 1000, 2000);

// Determine the LED behavior properties
unsigned long previousTimeLedBlinked = 0;
const unsigned long ledBlinkDelay = 1000;
byte ledState = LOW;

// Determine the release properties
unsigned long previousTimeRelease = 0;
const unsigned long releaseDelay = 12000;
const int releaseDuration = 1500;

// Declare the time properties
unsigned long timeNow = 0;
unsigned long timeReset = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // Start a stopwatch
  timeNow = millis() - timeReset;
  
  // Adjust the LED behavior accordingly to the release delay
  if (releaseDelay - timeNow <= 3000) {
    blink(ledBlinkDelay/4);
  }
  else {
  blink(ledBlinkDelay);
  }
  release();
}

void release() {
  // Check if the passed time is between the release range
  if ((timeNow > releaseDelay) && (timeNow <= releaseDelay + releaseDuration)) {
    blink(ledBlinkDelay/8);
    continuousServo.attach(servoPin);
    continuousServo.writeMicroseconds(mappedServoSpeed);
  }
  else if (timeNow > releaseDelay + releaseDuration) {
    continuousServo.detach();
    // Reset the stopwatch
    timeReset = millis();
  }
}

void blink(unsigned long blinkDelay) {
  // Make the LED blink
  if (timeNow - previousTimeLedBlinked >= blinkDelay) {
    previousTimeLedBlinked = timeNow;
    if (ledState == HIGH) {
      ledState = LOW;
    }
    else {
      ledState = HIGH;
    }
    digitalWrite(LED_BUILTIN, ledState);
  }
}

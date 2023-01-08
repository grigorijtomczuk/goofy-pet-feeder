#include <Servo.h>

Servo continuousServo;

// Determine general properties
const int servoPin = 8;
const int servoSpeed = 4;

// Map the servo speed value to a .writeMicroseconds() unit
const int mappedServoSpeed = map(servoSpeed, -50, 50, 1000, 2000);

// Determine the LED behavior properties
unsigned long previousTimeLedBlinked = 0;
const unsigned long ledBlinkDelay = 1000;
byte ledState = LOW;

// Determine the release properties
unsigned long previousTimeRelease = 0;
const unsigned long releaseDelay = 12000;
const int releaseDuration = 1000;

unsigned long timeNow = 0;
unsigned long timeReset = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("The thing's working!");
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

  // Start a "stopwatch"
  timeNow = millis() - timeReset;

  if (releaseDelay - timeNow <= 3000) {
    blink(ledBlinkDelay/4);
  }
  else {
    blink(ledBlinkDelay);
  }

  // Call the release() function everytime the release delay passes
  release();
}

void release() {
  if ((timeNow > releaseDelay) && (timeNow <= releaseDelay + releaseDuration)) {
    Serial.println("RELEASE");
    continuousServo.attach(servoPin);
    continuousServo.writeMicroseconds(mappedServoSpeed);
  }
  else if (timeNow > releaseDelay + releaseDuration) {
    continuousServo.detach();
    timeReset = millis();
    Serial.println("TIME RESETED!!!!!!!!!");
  }
}

void blink(unsigned long blinkDelay) {
  // Make the LED blink
  if (timeNow - previousTimeLedBlinked >= blinkDelay) {
    previousTimeLedBlinked = timeNow;
    Serial.println(timeNow);
    if (ledState == HIGH) {
      ledState = LOW;
    }
    else {
      ledState = HIGH;
    }
    digitalWrite(LED_BUILTIN, ledState);
  }
}

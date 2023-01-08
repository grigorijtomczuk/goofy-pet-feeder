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

void setup() {
  Serial.begin(9600);
  Serial.println("The thing's working!");
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

  // Start a "stopwatch"
  timeNow = millis();

  if (releaseDelay - (timeNow - previousTimeRelease) <= 3000) {
    fastBlink();
  }
  else {
    blink();
  }

  // Call the release() function everytime the release delay passes
  if (timeNow - previousTimeRelease >= releaseDelay) {
    previousTimeRelease += releaseDelay;
    release();
    // Reset the stopwatch to keep synchronized
    timeNow = 0;
  }
}

void release() {
  digitalWrite(LED_BUILTIN, HIGH);
  continuousServo.attach(servoPin);
  continuousServo.writeMicroseconds(mappedServoSpeed);
  delay(releaseDuration);
  continuousServo.detach();
}

void blink() {
  // Make the LED blink
  if (timeNow - previousTimeLedBlinked >= ledBlinkDelay) {
    previousTimeLedBlinked += ledBlinkDelay;
    if (ledState == HIGH) {
      ledState = LOW;
    }
    else {
      ledState = HIGH;
    }
    digitalWrite(LED_BUILTIN, ledState);
  }
}

void fastBlink() {
  // Make the LED blink faster
  if (timeNow - previousTimeLedBlinked >= (ledBlinkDelay / 4)) {
    previousTimeLedBlinked += (ledBlinkDelay / 4);
    if (ledState == HIGH) {
      ledState = LOW;
    }
    else {
      ledState = HIGH;
    }
    digitalWrite(LED_BUILTIN, ledState);
  }
}

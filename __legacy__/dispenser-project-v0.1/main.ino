#include <Servo.h>

Servo continuousServo;

// Determine general properties
const int servoPin = 8;
const int servoSpeed = 4;

// Map the servo speed to .writeMicroseconds() units
const int mappedServoSpeed = map(servoSpeed, -50, 50, 1000, 2000);

// Determine the LED behavior properties
unsigned long previousTimeLedBlinked = 0;
const unsigned long ledBlinkDelay = 1000;
byte ledState = LOW;

// Determine the release properties
unsigned long previousTimeRelease = 0;
const unsigned long releaseDelay = 10000;
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

  blink();

  // Call the release() function everytime the release delay passes
  if (timeNow - previousTimeRelease >= releaseDelay) {
    previousTimeRelease += releaseDelay;
    release();
    timeNow = 0;
  }
}

void release() {
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

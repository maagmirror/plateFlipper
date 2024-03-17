#include <Servo.h>
#include <ezButton.h>

//remove the wireless
//add function millis()
//tip: use the same power supply for the servo
//don't power the servo from the arduino
//but use the the same ground wire


// Constants
const int BUTTON_PIN_1 = 7;
const int BUTTON_PIN_2 = 6;
const int SERVO_PIN = 8;
const int LED_PIN = 13;

ezButton button1(BUTTON_PIN_1);
ezButton button2(BUTTON_PIN_2);

Servo servo;
int angle = 0;
bool servoActive = false;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
unsigned long lastToggleTime = 0;    // the last time the servo was toggled
const long toggleInterval = 500;     // interval at which to toggle servo (500ms)

void setup() {
  Serial.begin(9600);
  servo.attach(SERVO_PIN);
  pinMode(LED_PIN, OUTPUT);
  servo.write(angle);
}

void loop() {
  button1.loop();
  button2.loop();

  if (millis() - lastDebounceTime > debounceDelay) {
    handleButtonPress(button1);
    handleButtonPress(button2);
  }

  updateLED();
}

void handleButtonPress(ezButton& button) {
  if (button.isPressed()) {
    // Check if enough time has passed since last toggle to debounce
    if (millis() - lastToggleTime > toggleInterval) {
      toggleServo();
      lastToggleTime = millis(); // Update the last toggle time
    }
  }
}

void toggleServo() {
  angle = servoActive ? 0 : 90;
  servo.write(angle);
  servoActive = !servoActive;
  lastDebounceTime = millis(); // Reset the debouncing timer
}

void updateLED() {
  digitalWrite(LED_PIN, servoActive && abs(servo.read() - 90) <= 2 ? HIGH : LOW);
}

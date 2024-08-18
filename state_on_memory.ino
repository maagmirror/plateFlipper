#include <Servo.h>
#include <ezButton.h>
#include <EEPROM.h>

// Constants
const int BUTTON_PIN_1 = 7;
const int BUTTON_PIN_2 = 6;
//or 9
const int SERVO_PIN = 8;
const int LED_PIN = 13;
const int WIRELESS_PIN = 10; // Pin connected to SC2272-M4 output

ezButton button1(BUTTON_PIN_1);
ezButton button2(BUTTON_PIN_2);
ezButton wirelessButton(WIRELESS_PIN); // Treat the wireless signal as a button

Servo servo;
int angle = 0;
bool servoActive = false;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
unsigned long lastToggleTime = 0;
const long toggleInterval = 500;

void setup() {
  Serial.begin(9600);
  servo.attach(SERVO_PIN);
  pinMode(LED_PIN, OUTPUT);
  
  // Read the last saved angle from EEPROM
  angle = EEPROM.read(0); 
  if (angle != 0 && angle != 110) {
    angle = 0; // Default to 0 if an invalid value is read
  }
  
  servoActive = (angle == 110);
  servo.write(angle);
  updateLED(); // Update LED based on the servo position
}

void loop() {
  button1.loop();
  button2.loop();
  wirelessButton.loop(); // Treat the wireless signal as a button

  if (millis() - lastDebounceTime > debounceDelay) {
    handleButtonPress(button1);
    handleButtonPress(button2);
    handleButtonPress(wirelessButton); // Handle the wireless signal as a button press
  }
}

void handleButtonPress(ezButton& button) {
  if (button.isPressed()) {
    if (millis() - lastToggleTime > toggleInterval) {
      toggleServo();
      lastToggleTime = millis();
    }
  }
}

void toggleServo() {
  int newAngle = servoActive ? 0 : 110;
  
  if (newAngle != angle) { // Only write to EEPROM if the angle has changed
    angle = newAngle;
    EEPROM.write(0, angle);
  }
  
  servo.write(angle);
  servoActive = !servoActive;
  
  lastDebounceTime = millis(); // Reset the debouncing timer
  updateLED(); // Update LED based on the new servo position
}

void updateLED() {
  digitalWrite(LED_PIN, servoActive && abs(servo.read() - 110) <= 2 ? HIGH : LOW);
}

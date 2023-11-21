#include <Servo.h>
#include <ezButton.h>

// Constants
const int BUTTON_PIN_1 = 7; // Arduino pin connected to the first button's pin
const int BUTTON_PIN_2 = 1; // Arduino pin connected to the second button's pin
const int SERVO_PIN    = 9; // Arduino pin connected to servo motor's pin

// Create ezButton objects for both buttons
ezButton button1(BUTTON_PIN_1);
ezButton button2(BUTTON_PIN_2);

Servo servo;                 // create servo object to control a servo
int angle = 0;               // the current angle of the servo motor
int toangle = 120;           // angle you want to rotate

void setup() {
  Serial.begin(9600);         // initialize serial
  button1.setDebounceTime(50);// set debounce time to 50 milliseconds
  button2.setDebounceTime(50);// set debounce time to 50 milliseconds
  servo.attach(SERVO_PIN);    // attaches the servo on pin 9 to the servo object

  servo.write(angle);
}

void loop() {
  button1.loop(); // MUST call the loop() function for the first button
  button2.loop(); // MUST call the loop() function for the second button

  // Check the first button
  if (button1.isPressed()) {
    Serial.println("Button 1 is pressed");

    // Change angle of servo motor
    if (angle == 0)
      angle = toangle;
    else if (angle == toangle)
      angle = 0;

    // Control servo motor according to the angle
    servo.write(angle);
  }

  // Check the second button
  if (button2.isPressed()) {
    Serial.println("Button 2 is pressed");

    // Change angle of servo motor (you can customize this logic)
    if (angle == 0)
      angle = toangle;
    else if (angle == toangle)
      angle = 0;

    // Control servo motor according to the angle
    servo.write(angle);
  }
}

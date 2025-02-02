#include <Servo.h>
#include <ezButton.h>
#include <EEPROM.h>

// Definición de pines
const int BUTTON_PIN_1 = 7;
const int SERVO_PIN = 8;
const int LED_PIN = 13;

ezButton button1(BUTTON_PIN_1);

Servo servo;
int angle = 0;
bool servoActive = false;

unsigned long lastToggleTime = 0;
const long toggleInterval = 500; // Tiempo mínimo entre cambios de estado
const long debounceDelay = 50;   // Tiempo para filtrar rebotes

void setup() {
  delay(3000); // Espera inicial para estabilización

  Serial.begin(9600);
  servo.attach(SERVO_PIN);
  pinMode(LED_PIN, OUTPUT);

  button1.setDebounceTime(debounceDelay); // Configuración de debounce para el botón

  // Leer ángulo almacenado en EEPROM
  angle = EEPROM.read(0);
  if (angle != 0 && angle != 110) {
    angle = 0; // Si el valor leído es inválido, se establece por defecto en 0
  }

  servoActive = (angle == 110);
  servo.write(angle);
  updateLED();
}

void loop() {
  button1.loop(); // Actualiza el estado del botón

  // Solo actuar si el botón ha sido presionado y no es un falso positivo
  if (button1.isPressed()) {
    if (millis() - lastToggleTime > toggleInterval) { 
      toggleServo();
      lastToggleTime = millis(); // Actualiza el tiempo de la última activación
    }
  }
}

void toggleServo() {
  int newAngle = servoActive ? 0 : 110;

  if (newAngle != angle) { // Solo escribir en EEPROM si el ángulo cambió
    angle = newAngle;
    EEPROM.write(0, angle);
  }

  servo.write(angle);
  servoActive = !servoActive;
  updateLED();
}

void updateLED() {
  digitalWrite(LED_PIN, servoActive && abs(servo.read() - 110) <= 2 ? HIGH : LOW);
}

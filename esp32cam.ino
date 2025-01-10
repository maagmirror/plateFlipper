#include <Servo.h>
#include <ezButton.h>
#include <EEPROM.h>

// Pines del ESP32-CAM
const int BUTTON_PIN_1 = 12;  // Pin para el botón (GPIO12)
const int SERVO_PIN = 13;     // Pin para el servo (GPIO13)
const int LED_PIN = 4;        // LED integrado en el ESP32-CAM (GPIO4)

ezButton button1(BUTTON_PIN_1);

Servo servo;
int angle = 0;
bool servoActive = false;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 150;
unsigned long lastToggleTime = 0;
const long toggleInterval = 500;

void setup() {
  // Delay inicial para estabilizar
  delay(3000);

  Serial.begin(115200);
  servo.attach(SERVO_PIN);
  pinMode(LED_PIN, OUTPUT);

  // Inicializar EEPROM con tamaño suficiente
  EEPROM.begin(512);  // Tamaño de 512 bytes
  angle = EEPROM.read(0);

  if (angle != 0 && angle != 110) {
    angle = 0; // Default a 0 si se lee un valor no válido
  }

  servoActive = (angle == 110);

  servo.write(angle);
  updateLED(); // Actualizar LED según la posición del servo
}

void loop() {
  button1.loop();

  if (millis() - lastDebounceTime > debounceDelay) {
    handleButtonPress(button1);
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

  if (newAngle != angle) { // Solo escribir en EEPROM si el ángulo cambia
    angle = newAngle;
    EEPROM.write(0, angle);
    EEPROM.commit(); // Necesario en ESP32 para guardar cambios
  }

  servo.write(angle);
  servoActive = !servoActive;

  lastDebounceTime = millis(); // Reiniciar temporizador de rebote
  updateLED(); // Actualizar LED según la nueva posición del servo
}

void updateLED() {
  digitalWrite(LED_PIN, servoActive && abs(servo.read() - 110) <= 2 ? HIGH : LOW);
}

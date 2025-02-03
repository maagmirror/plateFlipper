#include <Servo.h>
#include <ezButton.h>
#include <EEPROM.h>

// Definición de pines
const int BUTTON_PIN_1 = 7;
const int SERVO_PIN = 8;
const int LED_PIN = 13;

const unsigned long TOGGLE_INTERVAL = 500;  // Tiempo entre activaciones
const unsigned long DEBOUNCE_DELAY = 50;    // Tiempo de debounce

ezButton button1(BUTTON_PIN_1);
Servo servo;
int angle = 0;
bool servoActive = false;
unsigned long lastToggleTime = 0;
int currentAngle = 0; // Almacena el estado real del servo

void setup() {
    // Configurar LED como salida y apagarlo inmediatamente para evitar parpadeo
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    delay(100); // Pequeño retardo para estabilizar energía antes de leer EEPROM

    Serial.begin(9600);
    pinMode(BUTTON_PIN_1, INPUT_PULLUP);  // Asegurar pull-up en el botón
    
    button1.setDebounceTime(DEBOUNCE_DELAY); // Configurar debounce del botón

    // Leer el estado del servo desde EEPROM
    angle = EEPROM.read(0);
    if (angle != 0 && angle != 110) {
        angle = 0;  // Si el valor leído es inválido, establecer en 0 por defecto
    }

    // Inicializar servo y establecer su última posición guardada
    servo.attach(SERVO_PIN);
    currentAngle = angle;
    servo.write(currentAngle);
    servoActive = (currentAngle == 110);

    updateLED(); // Asegurar que el LED refleje el estado inicial del servo
}

void loop() {
    button1.loop(); // Actualizar estado del botón

    if (button1.isReleased()) { // Detectar solo la transición de presionado a liberado
        if (millis() - lastToggleTime > TOGGLE_INTERVAL) {
            toggleServo();
            lastToggleTime = millis();
        }
    }
}

void toggleServo() {
    int newAngle = servoActive ? 0 : 110;

    if (newAngle != currentAngle) { // Solo actualizar si cambia
        EEPROM.update(0, newAngle);
        currentAngle = newAngle;
        servo.write(newAngle);
    }

    servoActive = !servoActive;
    updateLED();
}

void updateLED() {
    digitalWrite(LED_PIN, servoActive ? HIGH : LOW);
}
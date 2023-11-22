#include <Servo.h>
#include <ezButton.h>

// Constantes
const int BUTTON_PIN_1 = 7; // Pin de Arduino conectado al primer botón
const int BUTTON_PIN_2 = 2; // Pin de Arduino conectado al segundo botón
const int SERVO_PIN    = 9; // Pin de Arduino conectado al servo

// Crear objetos ezButton para ambos botones
ezButton button1(BUTTON_PIN_1);
ezButton button2(BUTTON_PIN_2);

Servo servo;                 // Crear objeto servo para controlar el servo
int angle = 0;               // Ángulo actual del servo
int toangle = 120;           // Ángulo al que deseas rotar

void setup() {
  Serial.begin(9600);         // Inicializar el puerto serie
  button1.setDebounceTime(50);// Establecer tiempo de rebote a 50 milisegundos
  button2.setDebounceTime(50);// Establecer tiempo de rebote a 50 milisegundos
  servo.attach(SERVO_PIN);    // Conectar el servo al pin 9

  servo.write(angle);
}

void loop() {
  button1.loop(); // DEBES llamar a la función loop() para el primer botón
  button2.loop(); // DEBES llamar a la función loop() para el segundo botón

  // Verificar el primer botón
  if (button1.isPressed()) {
    Serial.println("Botón 1 presionado");

    // Cambiar el ángulo del servo
    if (angle == 0)
      angle = toangle;
    else if (angle == toangle)
      angle = 0;

    // Controlar el servo según el ángulo
    servo.write(angle);
  }

  // Verificar el segundo botón
  if (button2.isPressed()) {
    Serial.println("Botón 2 presionado");

    // Cambiar el ángulo del servo (puedes personalizar esta lógica)
    if (angle == 0)
      angle = toangle;
    else if (angle == toangle)
      angle = 0;

    // Controlar el servo según el ángulo
    servo.write(angle);
  }
}

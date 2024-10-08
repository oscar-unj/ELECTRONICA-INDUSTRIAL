// Autor: Oscar Núñez Mori. Jaén, 08-Oct-2024
// Archivo: 4LED_OLED_I2C_Tiny4kOLED.ino

#include <Tiny4kOLED.h>

int previousKeyIndex = -1; // Para almacenar el índice anterior del teclado

// Definir los estados de los LEDs
int ledStates[] = {LOW, LOW, LOW, LOW};  // Estados iniciales para los LEDs (todos apagados)

// Definir los pines de los LEDs
const int ledPins[] = {2, 3, 4, 5};

// Usar PROGMEM para almacenar matrices en la memoria FLASH y liberar RAM
const int threshold[12] PROGMEM = {0, 78, 145, 247, 293, 334, 398, 428, 456, 500, 521, 541};
const char keyboard[12] PROGMEM = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '*', '0', '#'};

void setup() {
  // Inicialización de la pantalla OLED
  oled.begin();
  oled.clear();
  oled.on();
  
  // Configura el tamaño de la fuente
  oled.setFont(FONT8X16);
  
  // Inicialización del pin analógico
  pinMode(A0, INPUT);
  
  // Configurar los pines de los LEDs como salidas y asegurarse de que estén apagados
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], ledStates[i]);  // Apagar todos los LEDs inicialmente
  }
  
  // Mostrar el texto estático en la pantalla una vez
  oled.setCursor(0, 0);  // Establece la posición del cursor
  oled.print(F("Presionar Tecla:"));  // Usar F() para almacenar texto en FLASH
}

void loop() {
  // Leer el valor del pin analógico A0
  int sensorValue = analogRead(A0);
  
  // Determinar el índice correspondiente en la matriz `keyboard`
  int keyIndex = getKeyIndex(sensorValue);

  // Solo actualizar la pantalla si la tecla ha cambiado
  if (keyIndex != previousKeyIndex && keyIndex != -1) {
    oled.setCursor(60, 2);  // Posición del carácter en la pantalla
    oled.print(" ");       // Borra el carácter anterior
    oled.setCursor(60, 2);  // Regresa al inicio para escribir el nuevo carácter
    
    // Leer el carácter de la memoria FLASH
    char key = pgm_read_byte(&keyboard[keyIndex]);
    oled.print(key);  // Imprime la tecla correspondiente

    // Actualizar el valor anterior
    previousKeyIndex = keyIndex;
  }

  // Verificar si el valor actual es '1', '2', '3', o '4' para alternar LEDs individuales
  for (int i = 0; i < 4; i++) {
    if (keyIndex == i) {  // '1' a '4' corresponden a keyboard[0] a keyboard[3]
      ledStates[i] = !ledStates[i];  // Cambia el estado del LED
      digitalWrite(ledPins[i], ledStates[i]);  // Actualiza el estado del LED
      delay(300);  // Esperar 300ms para evitar fluctuaciones rápidas
    }
  }

  // Verificar si el valor actual es '*' (arranque secuencial)
  if (keyIndex == 9) {  // '*' corresponde a keyboard[9]
    startSequential();  // Iniciar arranque secuencial de LEDs
  }

  // Verificar si el valor actual es '#' (apagado total)
  if (keyIndex == 11) {  // '#' corresponde a keyboard[11]
    turnOffAll();  // Apagar todos los LEDs
  }

  // Esperar un poco antes de la siguiente lectura
  delay(100);
}

// Función para determinar el índice en la matriz `keyboard` con tolerancia de ±5
int getKeyIndex(int sensorValue) {
  // Comparar el valor de `sensorValue` con los umbrales usando tolerancia de ±5
  for (int i = 0; i < 12; i++) {
    // Leer el valor de threshold desde la memoria FLASH
    int thresh = pgm_read_word(&threshold[i]);
    if (sensorValue >= (thresh - 5) && sensorValue <= (thresh + 5)) {
      return i;  // Retorna el índice de la tecla correspondiente
    }
  }
  
  // Si el valor no coincide con ningún umbral, retornar -1
  return -1;
}

// Función para arranque secuencial de los LEDs con 4 segundos de espaciamiento
void startSequential() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPins[i], HIGH);  // Encender el LED correspondiente
    delay(4000);  // Esperar 4 segundos antes de encender el siguiente
  }
}

// Función para apagar todos los LEDs
void turnOffAll() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPins[i], LOW);  // Apagar el LED correspondiente
    ledStates[i] = LOW;  // Actualizar el estado a apagado
  }
}


// REFERENCIAS
// Basado en:
// [1]. Stephen Denne (s.f.). Tiny4kOLED. https://github.com/datacute/Tiny4kOLED
// [2]. OpenAI. (2024). ChatGPT (Ver. Oct. 08) [OLED I2C con Tiny4koled].
//      https://chatgpt.com/share/67059c2f-8774-8013-91a1-d71d491860c0





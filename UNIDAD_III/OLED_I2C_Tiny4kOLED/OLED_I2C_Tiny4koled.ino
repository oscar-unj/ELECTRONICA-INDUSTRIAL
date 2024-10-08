#include <Tiny4kOLED.h>

// Usar PROGMEM para almacenar matrices en la memoria FLASH y liberar RAM
const int  umbrales[12] PROGMEM = {  0,  78, 145, 247, 293, 334, 398, 428, 456, 500, 521, 541 };
const char teclas[12] PROGMEM   = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '*', '0', '#' };

int indiceTeclaAnterior = -1; // Para almacenar el índice anterior del teclado

void setup() {
  // Inicialización de la pantalla OLED
  oled.begin();
  oled.clear();
  oled.on();
  
  // Configura el tamaño de la fuente
  //oled.setFont(FONT8X16); // Letras más grandes más memoria FLASH
  oled.setFont(FONT6X8); // Letras más pequeñas menos memoria FLASH
  
  // Inicialización del pin analógico
  pinMode(A3, INPUT);    // A3 = 17
  
  // Mostrar el texto estático en la pantalla una vez
  oled.setCursor(0, 0);  // Establece la posición del cursor
  oled.print(F("APRETAR TECLA:"));  // Usar F() para almacenar texto en FLASH
}

void loop() {
  // Leer el valor del pin analógico A3 = 17
  int sensor = analogRead(A3);
  
  // Determinar el índice correspondiente en la matriz `teclas`
  int indiceTecla = obtieneIndiceTecla(sensor);

  // Solo actualizar la pantalla si la tecla ha cambiado
  if (indiceTecla != indiceTeclaAnterior && indiceTecla != -1) {
    oled.setCursor(40, 2);  // Posición del carácter en la pantalla
    oled.print(" ");        // Borra el carácter anterior
    oled.setCursor(40, 2);  // Regresa al inicio para escribir el nuevo carácter
    
    // Leer el carácter de la memoria FLASH
    char leeTecla = pgm_read_byte(&teclas[indiceTecla]);
    oled.print(leeTecla);  // Imprime la tecla correspondiente
    
    // Actualizar el valor anterior
    indiceTeclaAnterior = indiceTecla;
  }
  
  // Esperar un poco antes de la siguiente lectura
  delay(100);
}

// Función para determinar el índice en la matriz `tecla` con tolerancia de ±5
int obtieneIndiceTecla(int sensor) {
  // Comparar el valor de "sensor" con los umbrales usando tolerancia de ±5
  for (int i = 0; i < 12; i++) {
    // Leer el valor del umbral desde la memoria FLASH
    int umbral = pgm_read_word(&umbrales[i]);
    if (sensor >= (umbral - 5) && sensor <= (umbral + 5)) {
      return i;  // Retorna el índice de la tecla correspondiente
    }
  }
  // Si el valor no coincide con ningún umbral, retornar -1
  return -1;
}

// REFERENCIAS
// Basado en:
// [1]. Stephen Denne (). Tiny4kOLED. https://github.com/datacute/Tiny4kOLED
// [2]. OpenAI. (2024). ChatGPT (Ver. Oct. 08) [OLED I2C con Tiny4koled].
//      https://chatgpt.com/share/67054ef3-1d8c-8013-ab1e-b3d2f74c59dd
//

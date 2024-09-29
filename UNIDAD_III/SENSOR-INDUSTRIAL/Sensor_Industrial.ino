// Autor: Oscar NÚÑEZ MORI. Jaén 28-Sept-2024
// Archivo: Sensor_Industrial.ino

// Libreria para la pantalla LCD 16x2 y otras
#include <LiquidCrystal.h>

const int pinSensor = 19; // A5 - seleccionar la entrada para el sensor
int     valorSensor;      // valor de 0 a 1023
float  valorVoltaje;      // valor en voltaje

const int      rs =  7;  // RS. Selección de Registro
const int      en =  6;  // Enable. Habilita LCD
const  int     d4 =  5;  // Bit D4
const  int     d5 =  4;  // Bit D5
const  int     d6 =  3;  // Bit D6 
const  int     d7 =  2;  // Bit D7
// RW = 0 - A tierra para Escritura en el Circuito

// LiquidCrystal lcd(rs, en, d4, d5, d6, d7)
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// función de Cambio de escala decimal
float cambioEscala(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup()
{
  // Ajuste de columnas (16) y filas (2) del LCD
  lcd.begin(16,2);
}

void loop() {
   // Cursor en la primera posición (0) de la Primera Columna (0)
  lcd.setCursor(0, 0);
   // Tiempo
  lcd.print("Time:");
  lcd.print(millis()/1000);
  lcd.print("s");

  valorSensor = analogRead(pinSensor);   // realizar la lectura
  valorVoltaje = cambioEscala(valorSensor, 0, 1023, 0.0, 5.0); 

   // Cursor en la primera posición (0) de la Segunda Columna (1)
  lcd.setCursor(0, 1);
   // Valor del Sensor
  lcd.print("Valor: ");
  lcd.print(valorVoltaje);
  lcd.print("v");
  delay(100);

} // loop

// REFERENCIA
// Basado en:
// 1. Luis LLamas (2024). Entradas analógicas en Arduino.
//    https://www.luisllamas.es/entradas-analogicas-en-arduino/
// 2. Naylamp Mechatronics (s.f.). Tutorial LCD, conectando tu arduino a un LCD1602 y LCD2004
//    https://naylampmechatronics.com/blog/34_tutorial-lcd-conectando-tu-arduino-a-un-lcd1602-y-lcd2004.html


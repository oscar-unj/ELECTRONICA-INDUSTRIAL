// Autor: Oscar NÚÑÉZ MORI - 06-OCT-2024
// Archivo: Teclado_Matricial_un_Pin.ino

// Libreria para la pantalla LCD 16x2 y otras
#include <LiquidCrystal.h>

const  int     rs =  7;  // RS. Selección de Registro
const  int     en =  6;  // Enable. Habilita LCD
const  int     d4 =  5;  // Bit D4
const  int     d5 =  4;  // Bit D5
const  int     d6 =  3;  // Bit D6 
const  int     d7 =  2;  // Bit D7
// RW = 0 - A tierra para Escritura en el Circuito

// LiquidCrystal lcd(rs, en, d4, d5, d6, d7)
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

      int  tecla =  0;
      int      i =  0;
const int  pinTeclado = 19;  // A5

// Teclado Matricial 4x3 con un pin Analógico de Entrada
int  umbrales[12] = {   2,  77, 144, 244, 290, 331, 394, 424, 452, 496, 518, 538 }; 
char teclado[12]  = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '*', '0', '#' };

void setup() {

  // Ajuste de columnas (16) y filas (2) del LCD
  lcd.begin(16,2);
}

void loop () {
   // Cursor en la primera posición (0) de la Primera Columna (0)
  lcd.setCursor(0, 0);
  lcd.print("Teclado-Pantalla");

tecla = analogRead(pinTeclado);

  for (i = 0; i < 16; i++ ) {
    // es el PinTeclado es lo suficientemente cercano al valor del teclado 
    if( abs( tecla - umbrales[i] ) < 5 ) {
       // Cursor en la primera posición (0) de la Segunda Columna (1)
      lcd.setCursor(0, 1);
      // Valor de la tecla
      lcd.print(" Tecla: ");
      lcd.print(teclado[i]);
      lcd.print(" ");
      delay(100);
    } //if
  } //for
} //loop

// REFERENCIA. 
// Basado en: 
// Hari Wiguna (s.f.). How to read a 4x4 keypad using just one Arduino pin!
// https://youtu.be/G14tREsVqz0?si=ZTuKQwr4wQbBZtcF

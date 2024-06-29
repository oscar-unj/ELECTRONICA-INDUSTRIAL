// Autor. Oscar NÚÑEZ MORI. Jaén,  25-Junio-2024
// Definir los pines de los pulsadores y Motores
const int Arranque = 2;
const int Parada   = 8;
const int Motor01  = 14; // A0
const int Motor02  = 15; // A1
const int Motor03  = 16; // A2

void setup() {

  // Configurar pines de entrada y salida 
  pinMode(Arranque, INPUT);
  pinMode(Parada,   INPUT);
  pinMode(Motor01, OUTPUT);
  pinMode(Motor02, OUTPUT);
  pinMode(Motor03, OUTPUT);

}

void loop() {

 if( digitalRead(Arranque) ) {    // Prende motores secuencialmente
    
    digitalWrite(Motor01, HIGH);  // Enciende Motor 01
    delay(3000);  // Espera
    
    digitalWrite(Motor02, HIGH);  // Enciende Motor 01
    delay(3000);  // Espera

    digitalWrite(Motor03, HIGH);  // Enciende Motor 01
    delay(3000);  // Espera
 }       

 if( digitalRead(Parada) ) {     // Apaga motores secuencialmente
    
    digitalWrite(Motor01, LOW);  // Apaga Motor 01
    delay(3000);  // Espera
    
    digitalWrite(Motor02, LOW);  // Apaga Motor 01
    delay(2000);  // Espera

    digitalWrite(Motor03, LOW);  // Apaga Motor 01
    delay(3000);  // Espera
             
  } 
}



 


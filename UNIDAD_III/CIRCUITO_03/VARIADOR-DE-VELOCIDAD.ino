// Autor. Oscar NÚÑEZ MORI. Jaén,  25-Junio-2024
// Definir los pines de los pulsadores y Motores
const int ArranqueHorario      = 15;   // Pin A1  Analog
const int Parada               = 16;   // Pin A2  Analog
const int ArranqueAntiHorario  = 17;   // Pin A3  Analog
const int Velocidad            = 18;   // Pin A4  Analog
const int Switch01  = 4;   // Pin 4  Sw01  Digital
const int Switch02  = 2;   // Pin 2  Sw02  
const int Switch03  = 11;  // Pin 11 PWM Sw03  
const int Switch04  = 9;   // Pin 9  PWM SW04  
// Variables
int Memoria;
int Pwm;

void setup() {

  // Configurar pines de entrada 
  pinMode(ArranqueHorario,     INPUT);
  pinMode(Parada,              INPUT);
  pinMode(ArranqueAntiHorario, INPUT);
  pinMode(Velocidad,           INPUT);
  // Configurar pines de salida
  pinMode(Switch01, OUTPUT);
  pinMode(Switch02, OUTPUT);
  pinMode(Switch03, OUTPUT);
  pinMode(Switch04, OUTPUT);

}

void loop() {

 if( analogRead(ArranqueHorario) ) {  // 
    delay(100);
    digitalWrite(Switch02, LOW);   // 
    digitalWrite(Switch04, LOW);   // 
    delay(1000); //spera
    digitalWrite(Switch01, HIGH);  // 
    digitalWrite(Switch03, HIGH);  // 
    delay(100);// Espera

    while(1){
     Memoria = analogRead(Velocidad);
     Pwm = map(Memoria, 0, 1023, 0, 255);
     analogWrite(Switch03, Pwm);
     if( analogRead(Parada) ) {
        delay(100);// Espera
        digitalWrite(Switch01, LOW);  // 
        digitalWrite(Switch02, LOW);  // 
        digitalWrite(Switch03, LOW);  // 
        digitalWrite(Switch04, LOW);  // 
        delay(100);// Espera
        break;
      }
    
    }
 }       

 if( analogRead(ArranqueAntiHorario) ) {  // 
    delay(100);// Espera
    digitalWrite(Switch01, LOW);   // 
    digitalWrite(Switch03, LOW);   // 
    delay(1000); //spera
    digitalWrite(Switch02, HIGH);  // 
    digitalWrite(Switch04, HIGH);  // 
    delay(100);// Espera
    while(1){
      Memoria = analogRead(Velocidad);
      Pwm = map(Memoria, 0, 1023, 0, 255);
      analogWrite(Switch04, Pwm);
      if( analogRead(Parada) ) {
        delay(100);// Espera
        digitalWrite(Switch01, LOW);  // 
        digitalWrite(Switch02, LOW);  // 
        digitalWrite(Switch03, LOW);  // 
        digitalWrite(Switch04, LOW);  // 
        delay(100);// Espera
        break;
      }
    }   
 }       

 if( analogRead(Parada) ) {  //
    delay(100);// Espera
    digitalWrite(Switch01, LOW);  // 
    digitalWrite(Switch02, LOW);  // 
    digitalWrite(Switch03, LOW);  // 
    digitalWrite(Switch04, LOW);  // 
    delay(100);// Espera
 }  

}



 


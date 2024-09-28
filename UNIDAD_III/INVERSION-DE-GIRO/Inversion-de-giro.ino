// Autor. Oscar NÚÑEZ MORI. Jaén,  27-Sept-2024
// Arraque-Y-T.ino
// Arraque directo de motor trifasico estrella a triangulo

// Pulsadores, Contacto de Rele Térmico, Contactores

const int Hor       =  6;
const int Stop      =  5;
const int AntiHor   =  4;
const int ReleTerm  =  3;

const int Verde      = 14; // A0 - Giro HORARIO
const int Rojo       = 15; // A1 - PARADA
const int VerdeAH    = 16; // A2   Giro ANTIHORARIO
const int Amarillo   = 17; // A3   Luz de Relé Térmico del Motor

const int ContKA     = 18; // A4 ANTIHORARIO
const int ContKH     = 19; // A5 HORARIO

void setup() {
  // Configurar pines de entrada y salida 
  pinMode(Hor,       INPUT);
  pinMode(Stop,      INPUT);
  pinMode(AntiHor,   INPUT);  
  pinMode(ReleTerm,  INPUT);

  pinMode(Verde,    OUTPUT);  // Horario
  pinMode(Rojo,     OUTPUT);  // Stop
  pinMode(VerdeAH,  OUTPUT);  // Antihorario
  pinMode(Amarillo,  OUTPUT);  // Relé Térmico

  pinMode(ContKH,   OUTPUT);
  pinMode(ContKA,   OUTPUT);

  digitalWrite(Rojo,     LOW);   // Apaga Luz Roja
  digitalWrite(Verde,    LOW);   // Apaga Luz Verde
  digitalWrite(VerdeAH,  LOW);   // Apaga Luz Azul
  digitalWrite(Amarillo,  LOW);   // Apaga Luz Naranja

  digitalWrite(ContKH,   LOW);   // Desactiva Contactor KH
  digitalWrite(ContKA,   LOW);   // Desactiva Contactor KA
}

void loop() { 

  if( digitalRead(Hor) ) {    // Arranque Horario 
     delay(50); // evitar rebote    
     while( !digitalRead(Hor) ) { 
      digitalWrite(Verde,   HIGH);   // Enciende  Luz Verde
      digitalWrite(Rojo,     LOW);    // Desactiva Luz Roja
      digitalWrite(VerdeAH,  LOW);    // Desactiva Luz Azul
      digitalWrite(Amarillo,  LOW);    // Desactiva Luz Azul

      digitalWrite(ContKH,  HIGH);  // Activa Contactor K
      digitalWrite(ContKA,   LOW);  // Activa Contactor KY
      
      if( digitalRead(Stop) )     break;
      if( digitalRead(ReleTerm) ) break;
     }
 }       

  if( digitalRead(AntiHor) ) {    // Arranque Antihorario   
     delay(50); // evitar rebote    
     while( !digitalRead(AntiHor) ) { 
      digitalWrite(Verde,    LOW);    // Desactiva  Luz Verde
      digitalWrite(Rojo,     LOW);    // Desactiva Luz Roja
      digitalWrite(VerdeAH, HIGH);    // Activa Luz Azul
      digitalWrite(Amarillo, LOW);    // Desactiva Luz Azul

      digitalWrite(ContKH,   LOW);  // Activa Contactor K
      digitalWrite(ContKA,  HIGH);  // Activa Contactor KY

      if( digitalRead(Stop) )     break;
      if( digitalRead(ReleTerm) ) break;

     }
 } 

 if( digitalRead(Stop) ) {     // Parada
    delay(50); // evitar rebote 
    digitalWrite(Rojo,    HIGH);   // Enciende Luz Roja
    digitalWrite(Verde,    LOW);   // Apaga Luz Verde
    digitalWrite(VerdeAH,  LOW);   // Apaga Luz Azul 
    digitalWrite(Amarillo, LOW);   // Apaga Luz Naranja 

    digitalWrite(ContKH,   LOW);    // Desactiva Contactor KH
    digitalWrite(ContKA,  LOW);     // Desactiva Contactor KA

  } 

    while(digitalRead(ReleTerm) ) { 
      delay(50); // Evitar Rebote
      digitalWrite(Verde,     LOW);   // Desactiva Luz Verde
      digitalWrite(Rojo,      LOW);   // Desactiva Luz Roja
      digitalWrite(VerdeAH,   LOW);    // Desactiva Luz Azul
      digitalWrite(Amarillo, HIGH);  // Activa  Luz Naranja

      digitalWrite(ContKH,   LOW);  // Desactiva Contactor KH
      digitalWrite(ContKA,   LOW);  // Desactiva Contactor KA
    }

} // loop

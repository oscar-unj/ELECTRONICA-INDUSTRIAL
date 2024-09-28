// Autor: Oscar NÚÑEZ MORI. Jaén, 27-Sept-2024
// Archivo: Arraque-Y-T.ino
// Arraque Directo de Motor Trifásico Estrella a Triangulo

// Pulsadores, Contacto Rele Térmico, Contactores
int TiempoYT      = 5000; // 5 segundos (depende del motor)
int TiempoCambio  = 500;  // 0.5 segundos (debe ser 0.1 seg o menos)

const int Start     =  6;
const int Stop      =  5;
const int ReleTerm  =  4;

const int Verde     = 14; // A0
const int Rojo      = 15; // A1
const int Amarillo  = 16; // A2

const int ContKY    = 17; // A3 Contactor Estrella
const int ContKT    = 18; // A4 Contactor Trangulo
const int ContK     = 19; // A5 Contactor Principal

void setup() {
  // Configurar pines de entrada y salida 
  pinMode(Start,     INPUT);
  pinMode(Stop,      INPUT);
  pinMode(ReleTerm,  INPUT);

  pinMode(Verde,    OUTPUT); // Luz Verde de Start
  pinMode(Rojo,     OUTPUT); // Luz Roja de Stop
  pinMode(Amarillo, OUTPUT); // Luz de Relé Térmico

  pinMode(ContKY,   OUTPUT); // Contactor Estrella
  pinMode(ContKT,   OUTPUT); // Contactor Triangulo
  pinMode(ContK,    OUTPUT); // Contactor Principal

  digitalWrite(Rojo,     LOW);   // Apaga Luz Roja
  digitalWrite(Verde,    LOW);   // Apaga Luz Verde
  digitalWrite(Amarillo, LOW);   // Apaga Luz Amarilla 

  digitalWrite(ContK,   LOW);  // Desactiva Contactor K
  digitalWrite(ContKT,  LOW);  // Desactiva Contactor KT
  digitalWrite(ContKY,  LOW);  // Desactiva Contactor KY
}

void loop() {

  if( digitalRead(Start) ) {    // Prende   
    delay(50);  // evitar rebote
    digitalWrite(Verde,    HIGH);   // Enciende  Luz Verde
    digitalWrite(Rojo,     LOW);    // Desactiva Luz Roja
    digitalWrite(Amarillo, LOW);    // Desactiva Luz Amarilla

    digitalWrite(ContK,  HIGH);  // Activa Contactor K
    digitalWrite(ContKY, HIGH);  // Activa Contactor KY

    delay(TiempoYT);  // Tiempo para conmutación de KY a KT 
    digitalWrite(ContKY, LOW);  // Desactiva Contactor KY
   
    delay(TiempoCambio); // Evita cortocircuito entre KY y KT   
    digitalWrite(ContKT, HIGH);  // Activa Contactor KT
 }       

 if( digitalRead(Stop) ) {   // Parada
    delay(50);  // evitar rebote
    digitalWrite(Rojo,    HIGH);   // Enciende Luz Roja
    digitalWrite(Verde,    LOW);   // Apaga Luz Verde
    digitalWrite(Amarillo, LOW);   // Apaga Luz Amarilla 

    digitalWrite(ContK,   LOW);  // Desactiva Contactor K
    digitalWrite(ContKT,  LOW);  // Desactiva Contactor KT
    digitalWrite(ContKY,  LOW);  // Desactiva Contactor KY
  } 

 while( digitalRead(ReleTerm) ) { // Se arma el Rele Termico
    // Réle Térmico activado hasta desarme manual
    delay(50); // evitar rebote
    digitalWrite(Amarillo, HIGH);  // Enciende Luz Amarilla
    digitalWrite(Verde,     LOW);    // Apaga Luz Verde
    digitalWrite(Rojo,      LOW);     // Apaga Luz Roja

    digitalWrite(ContK,   LOW);  // Desactiva Contactor K
    digitalWrite(ContKT,  LOW);  // Desactiva Contactor KT
    digitalWrite(ContKY,  LOW);  // Desactiva Contactor KY
 } 

} // loop


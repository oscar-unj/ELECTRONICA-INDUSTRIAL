// Autor: Oscar NÚÑEZ MORI. Jaén,  28-Sept-2024
// Archivo: Mezclador.ino
// Mezclador con Motor Trifásico

// Pulsador, Contactores
      int TiempoHorario      = 4000;  // Tiempo Horario     (ms)
      int TiempoAntihorario  = 4000;  // Tiempo Antihorario (ms)
      int TiempoDesactivado  = 2000;  // Tiempo Desactivado (ms)
const int Start      =  6;
const int Verde      = 14; // A0 - Giro HORARIO
const int Rojo       = 15; // A1 - PARADA
const int VerdeAH    = 16; // A2   Giro ANTIHORARIO
const int ContKA     = 18; // A4 ANTIHORARIO
const int ContKH     = 19; // A5 HORARIO

void setup() {
  // Configurar pines de entrada y salida 
  pinMode(Start,     INPUT);

  pinMode(Verde,    OUTPUT);   // Horario
  pinMode(Rojo,     OUTPUT);   // Stop
  pinMode(VerdeAH,  OUTPUT);   // Antihorario
  pinMode(ContKH,   OUTPUT);
  pinMode(ContKA,   OUTPUT);

  digitalWrite(Rojo,     LOW);   // Apaga Luz Roja
  digitalWrite(Verde,    LOW);   // Apaga Luz Verde
  digitalWrite(VerdeAH,  LOW);   // Apaga Luz Verde AntiHoraria
  digitalWrite(ContKH,   LOW);   // Desactiva Contactor KH
  digitalWrite(ContKA,   LOW);   // Desactiva Contactor KA
  delay(2000); // 2 segundo de estabilización del sistema
}

void loop() {

      digitalWrite(Verde,   HIGH);   // Enciende  Luz Verde
      digitalWrite(Rojo,     LOW);   // Desactiva Luz Roja
      digitalWrite(VerdeAH,  LOW);   // Desactiva Luz Verde Antihoraria
      digitalWrite(ContKH,  HIGH);  // Activa Contactor K
      digitalWrite(ContKA,   LOW);  // Activa Contactor KY
      delay(TiempoHorario); // Tiempo Giro Horario
     
      digitalWrite(Verde,    LOW);  // Desactivada  Luz Verde
      digitalWrite(Rojo,    HIGH);  // Activada Luz Roja
      digitalWrite(VerdeAH,  LOW);  // Desactiva Luz Verde Antihoraria
      digitalWrite(ContKH,   LOW);  // Desactivado Contactor KH
      digitalWrite(ContKA,   LOW);  // Desactivado Contactor KY
      delay(TiempoDesactivado); // Tiempo Desactivado

      digitalWrite(Verde,    LOW);   // Enciende  Luz Verde
      digitalWrite(Rojo,     LOW);   // Desactiva Luz Roja
      digitalWrite(VerdeAH, HIGH);   // Desactiva Luz Verde Antihoraria
      digitalWrite(ContKH,   LOW);  // Activa Contactor K
      digitalWrite(ContKA,   HIGH);  // Activa Contactor KY
      delay(TiempoAntihorario); // Tiempo de Giro Antihorario

      digitalWrite(Verde,    LOW);  // Desactivada  Luz Verde
      digitalWrite(Rojo,    HIGH);  // Activada Luz Roja
      digitalWrite(VerdeAH,  LOW);  // Desactiva Luz Verde Antihoraria
      digitalWrite(ContKH,   LOW);  // Desactivado Contactor KH
      digitalWrite(ContKA,   LOW);  // Desactivado Contactor KY
      delay(TiempoDesactivado); // Tiempo Desactivado
} // loop

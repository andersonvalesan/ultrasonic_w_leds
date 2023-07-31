#include <Ultrasonic.h>

#define LED_BLUE 10
#define LED_YELLOW 11
#define LED_HIGH 12

#define PIN_POT A5
#define PIN_TRIG 6
#define PIN_ECHO 7

#define BUZZER 5

#define BUTTON 2

int tempo = 500;

struct MusicStruct {  //generating tones
 int A = 550;
 int As = 582;
 int B = 617;
 int C = 654;
 int Cs = 693;
 int D = 734;
 int Ds = 777;
 int E = 824;
 int F = 873;
 int Fs = 925;
 int G = 980;
 int Gs = 1003;
 int A2 = 1100;
 int A2s = 1165;
 int B2 = 1234;
 int C3 = 1308;
 int C3s = 1385;
 int D3 = 1555;
}Music;

struct LengthStruct {
 float half = 0.5;
 float one = 1.0;
 float one_half = 1.5;
 float two = 2.0;
 float two_half = 2.5;
}Length;

Ultrasonic ultrasonic(PIN_TRIG, PIN_ECHO);

void setup() {
  Serial.begin(9600);

  pinMode(PIN_POT, INPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_HIGH, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  pinMode(BUTTON, INPUT_PULLUP);

}

void loop() {
  int dist = printUltrasonic();

  int luminosidadeLED = map(analogRead(PIN_POT), 0, 1023, 0, 255); 

  if (dist < 10) { 
    analogWrite(LED_BLUE, luminosidadeLED);
    digitalWrite(LED_YELLOW, 0);
    digitalWrite(LED_HIGH, 0);   

    HP(); 
  } else if (dist >= 10 && dist < 30) {
    noTone(BUZZER);

    analogWrite(LED_YELLOW, luminosidadeLED);
    digitalWrite(LED_BLUE, 0);
    digitalWrite(LED_HIGH, 0);
  } else {
    noTone(BUZZER);

    analogWrite(LED_HIGH, luminosidadeLED);
    digitalWrite(LED_YELLOW, 0);
    digitalWrite(LED_BLUE, 0);
  }

  if (digitalRead(BUTTON) == LOW){
    GoT();
  }

}

int printUltrasonic(){
  int distancia = ultrasonic.read(CM);//ultrassom.Ranging(CM) retorna a distancia em centímetros(CM)
  Serial.print("Distância = ");//Imprime na serial o texto "Distância = "
  Serial.print(distancia); //Imprime na serial o valor da variável distancia
  Serial.println("cm"); //Imprime na serial o texto "cm"
  //delay(5000); //Intervalo de 1 segundo

  return distancia;
}

void setTone(int pin, int note, int duration) {
 tone(pin, note, duration);
 delay(duration);
 noTone(pin);
}

void HP(){
 setTone(BUZZER, Music.B, tempo * Length.one);
 setTone(BUZZER, Music.E, tempo * Length.one_half);
 setTone(BUZZER, Music.G, tempo * Length.half);
 setTone(BUZZER, Music.F, tempo * Length.one);
 setTone(BUZZER, Music.E, tempo * Length.two);
 setTone(BUZZER, Music.B2, tempo * Length.one);
 setTone(BUZZER, Music.A2, tempo * Length.two_half);
 setTone(BUZZER, Music.Fs, tempo * Length.two_half);
 setTone(BUZZER, Music.E, tempo * Length.one_half);
 setTone(BUZZER, Music.G, tempo * Length.half);
 setTone(BUZZER, Music.F, tempo * Length.one);
 setTone(BUZZER, Music.Ds, tempo * Length.two);
 setTone(BUZZER, Music.F, tempo * Length.one);
 setTone(BUZZER, Music.B, tempo * Length.two_half);
 delay(1000);
}

void GoT(){
  delay(1000);
  tone(BUZZER,440,tempo); //LA
  delay(tempo);
  tone(BUZZER,294,tempo); //RE
  delay(tempo);
  tone(BUZZER,349,tempo/2); //FA - O tempo/2 faz com que demore metade do valor estipulado anteriormente, pois essa parte é mais rápida
  delay(tempo/2);
  tone(BUZZER,392,tempo/2); //SOL
  delay(tempo/2);
  tone(BUZZER,440,tempo); //LA
  delay(tempo);
  tone(BUZZER,294,tempo); //RE
  delay(tempo);
  tone(BUZZER,349,tempo/2); //FA
  delay(tempo/2);
  tone(BUZZER,392,tempo/2); //SOL
  delay(tempo/2);
  tone(BUZZER,330,tempo); //MI
  delay(tempo);
}

#include "Wire.h"
#include "LiquidCrystal.h"
#include "DHT.h"
#define led_bleu 8
#define led_rouge 7
#define led_vert 9
#define led_jaune 10
#define ventilateur A0
#define LDR A2
#define bouton_demarrer 13
#define bouton_defile 11


LiquidCrystal lcd(1, 2, 3, 4, 5, 6);
DHT dht(A1, DHT11);

const int trigPin =A4;
const int echoPin =A3;
int value;
int etatbouton = 0;
boolean verif_dem = false; 
int compteur = 0;
int bouton = 0; 
boolean verif_defile = false;

// Variables utiles
long duree; // Durée de l'echo
int distance;

void setup() {
  lcd.begin(16, 2);
  dht.begin();
  pinMode(trigPin, OUTPUT); // Configuration du port du Trigger comme une SORTIE
  pinMode(echoPin, INPUT); // Configuration du port de l'Echo comme une ENTREE
  pinMode(LDR, INPUT);
  pinMode(bouton_demarrer, INPUT);
  pinMode(bouton_defile, INPUT);
  pinMode(12, OUTPUT);
  pinMode(led_bleu, OUTPUT);
  pinMode(led_rouge, OUTPUT);
  pinMode(led_vert, OUTPUT);
  pinMode(ventilateur, OUTPUT);
}

void loop() {                 
  // Émission d'un signal de durée 10 microsecondes
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Écoute de l'écho
  duree = pulseIn(echoPin, HIGH);

  // Calcul de la distance
  distance = duree*0.034/2;
  
  // Affichage de la distance dans le Moniteur Série
  lcd.print(" Distance en cm :") ;
  lcd.print(distance) ;
  
  if (distance <= 20 && distance > 10) {
    tone (12, 1900); // allume le buzzer actif arduino
    delay(500);
  } else if (distance <= 10 && distance > 5) {
    tone(12, 1900); // allume le buzzer actif arduino
    delay(300);
  } else if (distance <= 5) {
    tone(12, 1900); // allume le buzzer actif arduino
    delay(100);
  }
  noTone(12);

  lcd.print(" Humidity: ");
  lcd.print(h);

  lcd.print(" Temperature: ");
  lcd.print(t);

  if (t >= 10.00 && t < 19.00) {
    digitalWrite(led_bleu, HIGH);
  } else if (t >= 19.00 && t < 22.00) {
    digitalWrite(led_rouge, HIGH);    
  } else if (t > 22.00) {
    analogWrite(ventilateur, 128);    
  }

  if (h >= 40.00 && h <= 70.00){
    digitalWrite(led_vert, HIGH);
  } else {
    digitalWrite(led_jaune, HIGH);     
  }
      
  value = analogRead(LDR);

  lcd.print(" Luminosite : ");
  lcd.print(value);

  lcd.scrollDisplayLeft();  
  delay(300);
}
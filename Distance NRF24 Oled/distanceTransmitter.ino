//NRF24L01 Kütüphaneleri
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//Haberleşme Konfigürasyon
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "erkantiryaki0";
//Mesafe Sensörü Pin Ayarı
int echo = 2;            // Sensörün Echo pini
int trig = 3;            // Sensörün Trig pini

float sure, mesafe;      // Kullanacağımız değişkenleri tanımlıyoruz
 
void setup() {
  pinMode(trig, OUTPUT); // Trig pinini çıkış olarak ayarlıyoruz
  pinMode(echo, INPUT);  // Echo pinini giriş olarak ayarlıyoruz
  Serial.begin(9600);    // Seri Port Ekranı'nı başlatıyoruz
  //Haberleşme Başlangıç
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}
 
void loop() {
  mesafeOlcer();
  haberlesme();
}

void mesafeOlcer(){
  digitalWrite(trig, LOW);     // Trig pininin kapalı olduğundan emin olalım
  delayMicroseconds(5);        // Kısa bir süre bekleyelim
  digitalWrite(trig, HIGH);    // Trig pinini etkinleştirelim
  delayMicroseconds(10);       // Sensörün çalışması için ona zaman verelim
  digitalWrite(trig, LOW);     // Trig pinini kapatalım
  sure = pulseIn(echo, HIGH);  // Geri dönen yankının süresini kaydedelim
  mesafe = sure * 0.03432 / 2; // Ses hızını ve gidiş dönüş yolunu hesaplayarak gerçek mesafe değerini bulalım
  delay(100);   
}

void haberlesme(){
  //char text[] = (char)mesafe; // maksimium 32 karakter olabilir
  radio.write(&mesafe, sizeof(mesafe));
  delay(1000);
}
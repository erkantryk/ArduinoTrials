//NRF24L01 Kütüphaneleri
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//Oled Ekran Kütüphanesi
#include "U8glib.h"
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE); // Ekran nesnesini tanımla
//Haberleşme Konfigürasyon
RF24 radio(9, 10); // CE, CSN
const byte address[10] = "erkantiryaki0";
//Mesafe Değişkeni Tanımlama
float mesafe;
 
void setup() {
  //Haberleşme Setup
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  haberlesme(); 
  oledYazdir();
  delay(1000);
}

void haberlesme(){
  if (radio.available()) {
    //char text[32] = "";//print only 32 characters
    radio.read(&mesafe, sizeof(mesafe));
    Serial.print("Mesafe: ");
    Serial.print(mesafe,1);
    Serial.print(" cm");
    Serial.println("");
  }
}

void oledYazdir(){
  // Oluşturulan her çizim fonksiyonu için aşağıdaki 4 satır tekrar yazılabilir
  u8g.firstPage();  
  do {
    draw();
  } while (u8g.nextPage());
  delay(25);
}

void draw(void) { // Çizim fonksiyonu
  
  String Str;
  
  u8g.setFont(u8g_font_unifont);   // Font seçimi
  u8g.setPrintPos(10, 24);          // Ekran yerleşimi seçimi
  Str="Mesafe Olcer";
  u8g.print(Str); 
  u8g.setFont(u8g_font_profont12); // Font seçimi
  u8g.setPrintPos(0, 45);          // Ekran yerleşimi seçimi
  Str="Mesafe:"; 
  u8g.print(Str);

  u8g.setFont(u8g_font_profont12); // Font seçimi
  u8g.setPrintPos(50, 45);     
  u8g.print(mesafe);     


  
}


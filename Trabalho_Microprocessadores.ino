#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h> //biblioteca Adafruit p/ utilização do BMP 280
#include <LiquidCrystal.h> // biblioteca Liquid Crystal

LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // pinos do LCD - RS E D4 D5 D6 D7

#define PinButton (12)
#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

int x = 0; // contador do botao

Adafruit_BMP280 bmp; // I2C
//Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
//Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

void setup() {
  lcd.begin(16, 2); // inicializa LCD 16x2
  delay(500); // atraso de 0,5 segundos
  pinMode(PinButton, INPUT);
  Serial.begin(9600);
  while ( !Serial ) delay(100);   // wait for native usb
  Serial.println(F("BMP280 test"));
  unsigned status;
  //status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  status = bmp.begin(0x76);
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop() {
  lcd.clear(); // limpa tela do LCD

  if ( digitalRead(PinButton) == HIGH) // 
  {
    x = x + 1;
  }
  if (x == 3)
      {x=0;}
  
  if (x==0) // sem clique no botao
    {
    lcd.setCursor(0, 0); // selecionando coluna 0 e linha 0
    lcd.print("Temperatura: ");
    lcd.setCursor(1, 1); // selecionando coluna 1 e linha 1
    lcd.print(bmp.readTemperature()); // print no lcd da leitura do bmp p/ temperatura
    lcd.print(" ");
    lcd.print((char)223); // simbolo de grau
    lcd.print("C");}
  else if (x==1) //primeiro clique no botao
    {
    lcd.setCursor(0, 0); // selecionando coluna 0 e linha 0
    lcd.print("Pressao: ");
    lcd.setCursor(1, 1); // selecionando coluna 1 e linha 1
    lcd.print(bmp.readPressure()); // print no lcd da leitura do bmp p/ pressao
    lcd.print(" Pa");}
  else if (x==2) // segundo clique no botao
    {
    lcd.setCursor(0, 0); // selecionando coluna 0 e linha 0
    lcd.print("Altitude: ");
    lcd.setCursor(1, 1); // selecionando coluna 1 e linha 1
    lcd.print(bmp.readAltitude(1013.25)); // // print no lcd da leitura do bmp p/ altitude
    lcd.print(" m");}

    delay(200);
}

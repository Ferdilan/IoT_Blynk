#define BLYNK_TEMPLATE_ID "TMPL6vhE76WNW"
#define BLYNK_TEMPLATE_NAME "Kontrol Monitoring"
#define BLYNK_AUTH_TOKEN "NANGS4-kllDysgSJ1z-0nhf1grFqdS5e"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char ssid[] = "Kos Putra Lindisanti";
char pass[] = "password";

#define DHTPIN 4       
#define DHTTYPE DHT11

#define LDR_PIN 34 
#define LED1_PIN 12
#define LED2_PIN 13

DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer;

// --- Fungsi Kirim Data ke Blynk
void kirimSensorKeBlynk() {
  float suhu = dht.readTemperature();
  float kelembapan = dht.readHumidity();
  int cahaya = analogRead(LDR_PIN);

  Blynk.virtualWrite(V0, suhu);    // Kirim suhu ke V3
  Blynk.virtualWrite(V1, kelembapan);
  Blynk.virtualWrite(V2, cahaya);  // Kirim cahaya ke V4
}

// --- Kontrol LED1 dari Blynk (V1)
BLYNK_WRITE(V1) {
  int value = param.asInt();
  digitalWrite(LED1_PIN, value);
}

// --- Kontrol LED2 dari Blynk (V2)
BLYNK_WRITE(V2) {
  int value = param.asInt();
  digitalWrite(LED2_PIN, value);
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  dht.begin();
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);

  timer.setInterval(1000L, kirimSensorKeBlynk);  // Kirim data tiap 2 detik
}

void loop() {
  Blynk.run();
  timer.run();
}

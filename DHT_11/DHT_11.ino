// Sertakan library yang dibutuhkan
#include "DHT.h"

// Definisikan pin yang digunakan
#define DHTPIN 2       // Pin Data DHT11 terhubung ke pin D2
#define LEDPIN 8       // Pin LED terhubung ke pin D8

// Definisikan tipe sensor DHT
#define DHTTYPE DHT11  // Kita menggunakan DHT11

// Inisialisasi objek DHT
DHT dht(DHTPIN, DHTTYPE);

// Variabel untuk ambang batas suhu (dalam Celcius)
const float AMBANG_BATAS_SUHU = 30.0; 

void setup() {
  // Mulai komunikasi serial untuk debugging
  Serial.begin(9600);
  Serial.println("DHT11 LED Control Test");

  // Atur pin LED sebagai OUTPUT
  pinMode(LEDPIN, OUTPUT);

  // Mulai sensor DHT
  dht.begin();
}

void loop() {
  // Beri jeda 2 detik antar pembacaan sensor
  delay(2000);

  // Baca suhu dalam Celcius (default)
  float suhu = dht.readTemperature();
  // Baca kelembapan (opsional, jika ingin digunakan nanti)
  // float kelembapan = dht.readHumidity();

  // Cek apakah pembacaan gagal (sensor tidak terdeteksi)
  if (isnan(suhu)) {
    Serial.println("Gagal membaca dari sensor DHT!");
    return; // Keluar dari loop jika gagal
  }

  // Tampilkan data suhu ke Serial Monitor untuk debugging
  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.print(" °C");

  // Logika utama: Cek apakah suhu melebihi ambang batas
  if (suhu > AMBANG_BATAS_SUHU) {
    digitalWrite(LEDPIN, HIGH); // Nyalakan LED
    Serial.println(" | Suhu PANAS! LED Menyala.");
  } else {
    digitalWrite(LEDPIN, LOW);  // Matikan LED
    Serial.println(" | Suhu Normal. LED Mati.");
  }
}

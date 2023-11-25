#include <SoftwareSerial.h>

// Atur pin TX dan RX untuk komunikasi dengan ESP-01
SoftwareSerial espSerial(10, 11);

void setup() {
  // Inisialisasi komunikasi serial dengan baudrate 115200
  Serial.begin(115200);
  espSerial.begin(115200);

  // Tunggu modul WiFi ESP-01 untuk siap
  delay(1000);

  // Kirim perintah AT untuk menguji koneksi
  espSerial.println("AT\n");

}

void loop() {
  if (espSerial.available()) {
    // Baca data yang diterima dari ESP-01 dan kirim ke Serial Monitor
    char c = espSerial.read();
    Serial.write(c);
  }

  if (Serial.available()) {
    // Baca data yang diterima dari Serial Monitor dan kirim ke ESP-01
    char c = Serial.read();
    espSerial.write(c);
  }
}

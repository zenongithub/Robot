// Library untuk sensor ultrasonik
#include <NewPing.h>

// Definisi pin untuk sensor kiri
#define KIRI_TRIG_PIN A5
#define KIRI_ECHO_PIN A4

// Definisi pin untuk sensor tengah
#define TENGAH_TRIG_PIN A3
#define TENGAH_ECHO_PIN A2

// Definisi pin untuk sensor kanan
#define KANAN_TRIG_PIN A1
#define KANAN_ECHO_PIN A0

// Objek sensor untuk kiri, tengah, dan kanan
NewPing kiriSensor(KIRI_TRIG_PIN, KIRI_ECHO_PIN);
NewPing tengahSensor(TENGAH_TRIG_PIN, TENGAH_ECHO_PIN);
NewPing kananSensor(KANAN_TRIG_PIN, KANAN_ECHO_PIN);

void setup() {
  Serial.begin(9600); // Inisialisasi komunikasi serial
}

void loop() {
  // Membaca nilai dari sensor kiri
  int kiriDistance = kiriSensor.ping_cm();

  // Membaca nilai dari sensor tengah
  int tengahDistance = tengahSensor.ping_cm();

  // Membaca nilai dari sensor kanan
  int kananDistance = kananSensor.ping_cm();

  // Menampilkan nilai sensor ke Serial Monitor
  Serial.print("Sensor Kiri: ");
  Serial.print(kiriDistance);
  Serial.print(" cm\t");

  Serial.print("Sensor Tengah: ");
  Serial.print(tengahDistance);
  Serial.print(" cm\t");

  Serial.print("Sensor Kanan: ");
  Serial.print(kananDistance);
  Serial.println(" cm");

  delay(1000); // Menunggu 500 milidetik sebelum membaca ulang
}

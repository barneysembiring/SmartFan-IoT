const int trigPin = 2;     // Pin trigger sensor ultrasonik
const int echoPin = 3;     // Pin echo sensor ultrasonik
const int relayPin = 8;    // Pin output untuk mengontrol relay
const int lightSensorPin = A0;  // Pin analog untuk sensor cahaya
const int tempSensorPin = A1;   // Pin analog untuk sensor suhu

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relayPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Mengirimkan sinyal ultrasonik
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Menerima waktu pantulan ultrasonik
  long duration = pulseIn(echoPin, HIGH);

  // Menghitung jarak berdasarkan waktu pantulan
  // Kecepatan suara di udara adalah sekitar 343 meter/detik atau 0,0343 cm/mikrodetik
  int distance = duration * 0.0343 / 2;

  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Membaca nilai sensor cahaya
  int lightValue = analogRead(lightSensorPin);

  Serial.print("Nilai Cahaya: ");
  Serial.println(lightValue);

  // Membaca nilai sensor suhu
  int tempValue = analogRead(tempSensorPin);
  float temperature = (tempValue * 5.0 / 1023.0 - 0.5) * 100.0;

  Serial.print("Suhu: ");
  if (temperature < 10) {
    Serial.print("0");
  }
  Serial.print(temperature, 2);  // Tampilkan 2 digit desimal
  Serial.println(" derajat Celsius");

  // Memeriksa kondisi siang atau malam
  if (lightValue >= 500) {
    // Siang hari
    if (temperature > 33 && distance >= 5) {
      digitalWrite(relayPin, HIGH);  // Menghidupkan relay
      Serial.println("Kipas OFF");
    } else {
      digitalWrite(relayPin, LOW);   // Mematikan relay
      Serial.println("Kipas ON");
    }
  } else {
    // Malam hari
    if (temperature > 28 && distance >= 5) {
      digitalWrite(relayPin, HIGH);  // Menghidupkan relay
      Serial.println("Kipas OFF");
    } else {
      digitalWrite(relayPin, LOW);   // Mematikan relay
      Serial.println("Kipas ON");
    }
  }

  delay(500);  // Jeda antara pembacaan sensor
}


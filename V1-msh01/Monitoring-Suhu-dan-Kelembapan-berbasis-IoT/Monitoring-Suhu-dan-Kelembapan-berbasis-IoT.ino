// Monitoring Suhu dan Kelembapan Berbasis IoT (display OLED)
// Project by: Maftuh Siroj Hamdani
// Version = BETA

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <DHT.h>
#include <Wire.h>

#define DHTPIN A0       // Pin sensor DHT11
#define DHTTYPE DHT11

#define LED_PIN 8       // Pin LED
#define BUZZER_PIN 9    // Pin Buzzer

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_I2C_ADDR 0x3C  // Alamat I2C OLED (0x3C atau 0x3D)

// Inisialisasi sensor dan OLED
DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Inisialisasi OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_I2C_ADDR)) {
    Serial.println("OLED gagal diinisialisasi");
    for (;;);
  }

  display.clearDisplay();

  // -------------------------
  // Animasi Loading
  // -------------------------
  for (int i = 0; i <= SCREEN_WIDTH; i += 8) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Loading...");

    display.fillRect(0, 20, i, 10, SSD1306_WHITE); // Bar loading
    display.drawRect(0, 20, SCREEN_WIDTH, 10, SSD1306_WHITE); // Border bar

    display.display();
    delay(100); // kecepatan animasi
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 20);
  display.println("Ready!");
  display.display();
  delay(1000);
}

void loop() {
  float suhu = dht.readTemperature();    // membaca suhu
  float kelembapan = dht.readHumidity(); // membaca kelembapan

  // cek error sensor
  if (isnan(suhu) || isnan(kelembapan)) {
    Serial.println(F("Gagal membaca dari DHT11"));
    return;
  }

  // tampilkan di OLED
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.print("Suhu: ");
  display.print(suhu);
  display.println(" C");

  display.setCursor(0, 30);
  display.print("Humid: ");
  display.print(kelembapan);
  display.println(" %");

  display.display();

  // Logika LED & Buzzer
  if (suhu > 30.0) {
    digitalWrite(BUZZER_PIN, HIGH);
    blinkLED(10); // kedip cepat
  } else if (suhu < 18.0) {
    digitalWrite(BUZZER_PIN, HIGH);
    blinkLED(500); // kedip lambat
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
  }

  delay(1000); // update tiap  1 detik
}

// Fungsi kedip LED
void blinkLED(int interval) {
  digitalWrite(LED_PIN, HIGH);
  delay(interval);
  digitalWrite(LED_PIN, LOW);
  delay(interval);
}

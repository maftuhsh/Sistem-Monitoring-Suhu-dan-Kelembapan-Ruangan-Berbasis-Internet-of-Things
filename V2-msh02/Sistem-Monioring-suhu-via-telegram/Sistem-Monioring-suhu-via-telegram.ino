#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <DHT.h>

#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define BUZZER D2   // buzzer di pin D2

// ====== Ganti dengan data kamu ======
const char* ssid = "speedy@e6a0";
const char* password = "Gbrgembrung";

#define BOTtoken "8308704526:AAH8q1pkoz7ARvKSCf-amQOp0haHR0NuGEw"   // Token dari BotFather
#define CHAT_ID "8091103824"      // Chat ID kamu

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

unsigned long lastTime = 0;
unsigned long timerDelay = 60000; // setiap 60 detik kirim data

void setup() {
  Serial.begin(9600);
  Serial.println("ESP8266 siap!");
  dht.begin();

  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, HIGH); // matikan buzzer awal (aktif low)

  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi Terhubung!");
 

  client.setInsecure(); // bypass sertifikat SSL
  bot.sendMessage(CHAT_ID, "[🤖] Menghubungkan WiFi......", "");
  bot.sendMessage(CHAT_ID, "[🤖] Berhasil terhubung ke WiFi......", "");
  bot.sendMessage(CHAT_ID, "[🤖] ✅ ESP8266 Online! Monitoring suhu dimulai.", "");
}

void loop() {
  if (millis() - lastTime > timerDelay) {
    float suhu = dht.readTemperature();
    float lembab = dht.readHumidity();

    if (isnan(suhu) || isnan(lembab)) {
      Serial.println("Gagal baca sensor DHT!");
      return;
    }

    String pesan = "🌡 Suhu: " + String(suhu) + "°C\n💧 Kelembaban: " + String(lembab) + "%";

    // Kondisi suhu tinggi → buzzer nyala
    if (suhu > 30) {
      digitalWrite(BUZZER, LOW); // buzzer ON (aktif low)
      bot.sendMessage(CHAT_ID, "[🤖] ⚠️ ALERT! Suhu tinggi: " + String(suhu) + "°C", "");
      bot.sendMessage(CHAT_ID, "[🤖] kamarmu panas banget woii kipasinn sekarang!!......", "");
    } else {
      digitalWrite(BUZZER, HIGH); // buzzer OFF
    }

    bot.sendMessage(CHAT_ID, pesan, "");
    Serial.println("Data dikirim ke Telegram: " + pesan);

    lastTime = millis();
  }

  // Command manual dari Telegram
  int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  while(numNewMessages) {
    for (int i = 0; i < numNewMessages; i++) {
      String chat_id = String(bot.messages[i].chat_id);
      String text = bot.messages[i].text;

      if (text == "/status") {
        float suhu = dht.readTemperature();
        float lembab = dht.readHumidity();
        String reply = "[🤖] Status sekarang:\n🌡 Suhu: " + String(suhu) + "°C\n💧 Kelembaban: " + String(lembab) + "%";
        bot.sendMessage(chat_id, reply, "");
      }
      else if (text == "/off") {
        digitalWrite(BUZZER, HIGH); // matikan buzzer melalui tele
        bot.sendMessage(chat_id, "[🤖] 🔕 Buzzer berhasil dimatikan .", "");
      }
      else if (text == "/on") {
        digitalWrite(BUZZER, LOW); // hidupkan buzzer melalui tele
        bot.sendMessage(chat_id, "[🤖] 🔔 Buzzer Berhasil dinyalakan .", "");
      }
    }
    numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  }
}

### Update logs
- version : msh02

## software used :
- Git & Github (repository)
- Arduino IDE (programing)
- wokwi (simulation wiring)
- Web Arduino (reference)

---

## Hardware used :
- Kabel jumper 7x
- USB to type B
- ESP32 8266 (WiFimodule)
- Sensor DHT11
- Buzzer
- Project Board

---

## version : v.msh02.01
- New :
> Arduino -> Esp32 8266 (Wifi Module)

> Monitoring Via Telegram (Bot API)

> buzzer -> alarm ketika suhu diatas 30 derajat

- note :
    - penampilan suhu akan ditampilnkan setiap menit pada telegram
    - buzzer berbunyi jika suhu > 30 dan akan memberi notif pada bot telegram
    - proses mendeteksi suhu dan lembab agak sedikit melambat karena menggunakan sensor     dht11 makanya hanya bisa membaca suhu per detik

---

> devby:msh
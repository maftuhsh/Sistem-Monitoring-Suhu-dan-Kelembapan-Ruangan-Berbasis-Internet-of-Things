### Update logs
- version : msh01

## software used :
- Git & Github (repository)
- Arduino IDE (programing)
- wokwi (simulation wiring)
- Web Arduino (reference)
---
## Hardware used :
- Kabel jumper 14x
- USB to TTL
- Arduino Uno R3 (dip)
- Lcd Oled 0.96
- Sensor DHT11
- LED
- Buzzer
---
- Project Board
## version : v.msh01.01
- New :
> Skema wiring 

![alt text]({4147AA93-E651-4F01-B5D8-DE519F2F9CCB}.png)

> loading sebelum monitoring
> Led-> Alarm
> buzzer -. alarm

- note :
    - Led akan berkedip dan buzzer berbunyi pada saat suhu diatas 30 derajat celcius dan dibawah 18 derajat celcius
    - proses mendeteksi suhu dan lembab agak sedikit melambat karena menggunakan sensor dht11 makanya hanya bisa membaca suhu per detik

---

> devby:msh
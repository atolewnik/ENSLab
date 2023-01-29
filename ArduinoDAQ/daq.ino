#include <DHT.h>
#include <DHT_U.h>

#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include <DS3231.h>

#define DHTPIN 2 
#define DHTTYPE DHT11

DS3231 rtc_instance;
RTCDateTime dt;
File dataFile;

DHT dht(DHTPIN, DHTTYPE);


void setup() {
  Serial.begin(9600);
  Serial.println("Initialize DS3231");
  rtc_instance.begin();
  rtc_instance.setDateTime(__DATE__, __TIME__);
  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  /* Measure temperature and humidity.  If the functions returns
     true, then a measurement is available. */
  
  dataFile = SD.open("data.txt", FILE_WRITE);
  dt = rtc_instance.getDateTime();

  dataFile.print(dt.year); dataFile.print("-");
  dataFile.print(dt.month); dataFile.print("-"); 
  dataFile.print(dt.day); dataFile.print(" "); 
  dataFile.print(dt.hour); dataFile.print(":"); 
  dataFile.print(dt.minute); dataFile.print(":"); 
  dataFile.print(dt.second); dataFile.println("");
  dataFile.print(F("Humidity: "));
  dataFile.print(h);
  dataFile.print(F("%  Temperature: "));
  dataFile.print(t);
  dataFile.print(F("°C "));
 
  dataFile.close();
  delay(1000);

}

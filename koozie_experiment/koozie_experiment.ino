//Include libraries

#include <DHT.h>
#include <DHT_U.h>

#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include <DS3231.h>

#include <OneWire.h>
#include <DallasTemperature.h>

// Pins and variables declaration
#define DHTPIN 5
#define DHTTYPE DHT11
#define ONE_WIRE_BUS 3
#define thermistorPin 0

static int i = 0;

DS3231 rtc_instance;
RTCDateTime dt;
File dataFile;

DHT dht(DHTPIN, DHTTYPE);

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

void setup() {
  // Initialize Real time clock and sd card module 
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

  // Read thermistor Analog value and calculate temperature from analog value
  int thermistorReading = analogRead(thermistorPin);
  double tempK = log(10000.0 * ((1024.0 / thermistorReading - 1)));
  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) *tempK );
  float thermistorTemp = tempK - 207.15;


  sensors.requestTemperatures(); 
  
  // with "byIndex" you can have more than one IC on the same bus. 0 refers to the first IC on the wire
  float probeTemp = sensors.getTempCByIndex(0);

  // Read temperature as Celsius (the default)
  float dhtTemp = dht.readTemperature();

  // Measure temperature and humidity.  If the functions returnstrue, then a measurement is available.
  
  // Open the file and write to the SD card
  Serial.println(thermistorTemp);
  dataFile = SD.open("data.txt", FILE_WRITE);
  dt = rtc_instance.getDateTime();
  
  dataFile.print("Sample - "); dataFile.println(i);

  dataFile.print("Timestamp: "); dataFile.print(dt.year); dataFile.print("-");
  dataFile.print(dt.month); dataFile.print("-"); 
  dataFile.print(dt.day); dataFile.print(" "); 
  dataFile.print(dt.hour); dataFile.print(":"); 
  dataFile.print(dt.minute); dataFile.print(":"); 
  dataFile.print(dt.second); dataFile.println("\n");
  dataFile.print(F("Liquid Temperature: "));
  dataFile.print(probeTemp);
  dataFile.println(F("°C "));

  dataFile.print(F("Wall Temperature: "));
  dataFile.print(thermistorTemp);
  dataFile.println(F("°C "));

  dataFile.print(F("Environment Temperature: "));
  dataFile.print(dhtTemp);
  dataFile.println(F("°C "));
  dataFile.println("---------------------------------");
  dataFile.close();
  
  i = i + 1;
  
  delay(30000);
}

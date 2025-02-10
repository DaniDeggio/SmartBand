#include <DFRobot_MAX30102.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

DFRobot_MAX30102 particleSensor;
Adafruit_MPU6050 mpu;

// Variabili per il MAX30102
int32_t SPO2; // SPO2
int8_t SPO2Valid; // Flag per verificare se il calcolo di SPO2 è valido
int32_t heartRate; // Frequenza cardiaca
int8_t heartRateValid; // Flag per verificare se il calcolo della frequenza cardiaca è valido

// Variabili per l'MPU6050
sensors_event_t a, g, temp;

void setup() {
  // Inizializza la seriale
  Serial.begin(115200);

  // Imposta il bus I2C con SDA su GPIO5 e SCL su GPIO6
  Wire.begin(5, 6);
  
  // Inizializza il sensore MAX30102
  while (!particleSensor.begin()) {
    Serial.println("MAX30102 non trovato");
    delay(1000);
  }
  
  // Configura il MAX30102
  particleSensor.sensorConfiguration(/*ledBrightness=*/50, /*sampleAverage=*/SAMPLEAVG_4, \
                        /*ledMode=*/MODE_MULTILED, /*sampleRate=*/SAMPLERATE_100, \
                        /*pulseWidth=*/PULSEWIDTH_411, /*adcRange=*/ADCRANGE_16384);

  // Inizializza il sensore MPU6050
  if (!mpu.begin()) {
    Serial.println("MPU6050 non trovato!");
    while (1) {
      delay(10);
    }
  }
  
  // Configura il MPU6050
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  Serial.println("Sensori inizializzati");
}

void loop() {
  // Leggi e stampa i dati dal sensore MAX30102
  Serial.println(F("Attendere circa quattro secondi..."));
  particleSensor.heartrateAndOxygenSaturation(&SPO2, &SPO2Valid, &heartRate, &heartRateValid);

  Serial.print(F("heartRate="));
  Serial.print(heartRate, DEC);
  Serial.print(F(", heartRateValid="));
  Serial.print(heartRateValid, DEC);
  Serial.print(F("; SPO2="));
  Serial.print(SPO2, DEC);
  Serial.print(F(", SPO2Valid="));
  Serial.println(SPO2Valid, DEC);

  // Leggi e stampa i dati dal sensore MPU6050
  mpu.getEvent(&a, &g, &temp);
  Serial.print("Accelerometro X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.println(a.acceleration.z);

  Serial.print("Giroscopio X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.println(g.gyro.z);

  Serial.print("Temperatura: ");
  Serial.print(temp.temperature);
  Serial.println(" C");

  delay(1000); // Pausa tra le letture
}

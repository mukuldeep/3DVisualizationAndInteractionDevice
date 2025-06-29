#include <Wire.h>
#include <Adafruit_MPU6050.h>

Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  while (!Serial)
    delay(10); // Wait for Serial Monitor to open

  Wire.begin();
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_2000_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  sensors_event_t accel, gyro, temp;
  mpu.getEvent(&accel, &gyro, &temp);

  float roll = atan2(-accel.acceleration.y, accel.acceleration.z) * 180.0 / PI;
  float pitch = atan2(accel.acceleration.x, sqrt(accel.acceleration.y * accel.acceleration.y + accel.acceleration.z * accel.acceleration.z)) * 180.0 / PI;

  //Serial.print("Roll: ");
  Serial.println(roll);
  //Serial.print(" degrees, Pitch: ");
  //Serial.print(pitch);
  //Serial.println(" degrees");

  delay(10); // Delay between measurements
}

#include <Wire.h>
#include <Adafruit_MPU6050.h>

Adafruit_MPU6050 mpu;
  static float accumulatedYaw = 0.0;
void setup() {
  Serial.begin(9600);
  while (!Serial)
    delay(10); // Wait for Serial Monitor to open

  Wire.begin();
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  sensors_event_t gyro;
  mpu.getEvent(NULL, &gyro, NULL);

  float yaw = gyro.gyro.z * 0.1; // Scale gyro rate to get change in yaw angle

  accumulatedYaw += yaw;

  //Serial.print("Head movement: ");
  Serial.println(accumulatedYaw);
  //Serial.println(" degrees");

  delay(10); // Delay between measurements
}

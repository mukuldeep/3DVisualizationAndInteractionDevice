#include <Wire.h>
#include <Adafruit_MPU6050.h>

Adafruit_MPU6050 mpu;
static float acc_yaw=0.0;
void setup() {
  Serial.begin(9600);
  while (!Serial)
    delay(10); // Wait for Serial Monitor to open

  Wire.begin();
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  sensors_event_t accel, gyro, temp;
  mpu.getEvent(&accel, &gyro , &temp);

//  float roll = atan2(accel.acceleration.x, accel.acceleration.z) * 180.0 / PI;
//  float pitch = atan2(-accel.acceleration.y, sqrt(accel.acceleration.x * accel.acceleration.x + accel.acceleration.z * accel.acceleration.z)) * 180.0 / PI;
//  float yaw = atan2(accel.acceleration.z, sqrt(accel.acceleration.x * accel.acceleration.x + accel.acceleration.y * accel.acceleration.y)) * 180.0 / PI;
//
//
//  Serial.print("Roll: ");
//  Serial.print(roll);
//  Serial.print(" degrees, Pitch: ");
//  Serial.print(pitch);
//  Serial.print(" degrees, Yaw: ");
//  Serial.print(yaw);
//  Serial.println(" degrees");
    acc_yaw+=(gyro.gyro.x)+0.093;
    float angle=-acc_yaw*7;
    Serial.print("yaw:");
    Serial.print(acc_yaw);
    Serial.print(" angle:");
    Serial.println(angle);

  delay(100); // Delay between measurements
}

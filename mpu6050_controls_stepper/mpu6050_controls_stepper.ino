#include <Stepper.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>

/* MPU6050 */
Adafruit_MPU6050 mpu;
static float acc_yaw=0.0;

/* stepper motor*/
const int stepsPerRevolution = 200;
// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

//stepper motor rotate by angle in degree
void rotate_by_angle(int angle){
  int steps=(stepsPerRevolution*angle)/360;
  myStepper.step(steps);
}

/* angle state */
int pre_angle=0;

void setup() {
  myStepper.setSpeed(60);//stepper motor rpm

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

void angle_to_move(int angle){
  Serial.print(" angle_to_move:");
  Serial.println(angle-pre_angle);
}

void loop() {
  sensors_event_t accel, gyro, temp;
  mpu.getEvent(&accel, &gyro , &temp);
  acc_yaw+=(gyro.gyro.x)+0.093;
  float angle=-acc_yaw*7;
  Serial.print("yaw:");
  Serial.print(acc_yaw);
  Serial.print(" angle:");
  Serial.print(angle);
  Serial.print(" angle_to_move:");
  Serial.println(angle-pre_angle);
  rotate_by_angle(angle-pre_angle);
  pre_angle+=(int)(angle-pre_angle);
  

  delay(100);
}

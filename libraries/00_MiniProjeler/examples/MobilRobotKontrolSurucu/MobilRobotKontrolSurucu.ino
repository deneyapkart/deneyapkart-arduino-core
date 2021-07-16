// Iki farkli Deneyap Kart'in esp-now protokolunu kulanarak birbirleriyle haberlesmesi (motor surcu tarafi)

#include <Arduino.h>
#include "deneyap.h"
#include "WiFi.h"
#include "esp_now.h"

#define MOT1_DIRA D0
#define MOT1_DIRB D1
#define MOT2_DIRA D4
#define MOT2_DIRB D5

void motor_stop();
void motor_forward();
void motor_backward();
void motor_right();
void motor_left();

typedef struct struct_message {
    float accel_x;
    float accel_y;
    float accel_z;
} struct_message;

struct_message imuData;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&imuData, incomingData, sizeof(imuData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Float: ");
  Serial.println(imuData.accel_x);
  Serial.print("Float: ");
  Serial.println(imuData.accel_y);
  Serial.print("Float: ");
  Serial.println(imuData.accel_z);
  Serial.println();

  if(imuData.accel_x < 0.5 && imuData.accel_x > -0.5 && 
     imuData.accel_y < 0.5 && imuData.accel_y > -0.5)
    motor_stop();
  else if(imuData.accel_y < -0.5)
    motor_forward();
  else if(imuData.accel_y > 0.5)
    motor_backward();
  else if(imuData.accel_x < -0.5)
    motor_right();
  else if(imuData.accel_x > 0.5)
    motor_left();
}

void setup() {
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_STA);

  /*pinMode(MOT1_DIRA, OUTPUT);
  pinMode(MOT1_DIRB, OUTPUT);
  pinMode(MOT2_DIRA, OUTPUT);
  pinMode(MOT2_DIRB, OUTPUT);*/

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {

}

void motor_stop()
{
  writeRedLed(LOW);
  writeGreenLed(LOW);
  writeBlueLed(LOW);

  digitalWrite(MOT1_DIRA, LOW);
  digitalWrite(MOT1_DIRB, LOW);
  digitalWrite(MOT2_DIRA, LOW);
  digitalWrite(MOT2_DIRB, LOW);

  Serial.println("DUR");
}

void motor_forward()
{
  writeRedLed(HIGH);
  writeGreenLed(LOW);
  writeBlueLed(LOW);

  digitalWrite(MOT1_DIRA, HIGH);
  digitalWrite(MOT1_DIRB, LOW);
  digitalWrite(MOT2_DIRA, HIGH);
  digitalWrite(MOT2_DIRB, LOW);

  Serial.println("İLERİ");
}

void motor_backward()
{
  writeRedLed(LOW);
  writeGreenLed(HIGH);
  writeBlueLed(LOW);

  digitalWrite(MOT1_DIRA, LOW);
  digitalWrite(MOT1_DIRB, HIGH);
  digitalWrite(MOT2_DIRA, LOW);
  digitalWrite(MOT2_DIRB, HIGH);
  
  Serial.println("GERİ");
}

void motor_right()
{
  writeRedLed(LOW);
  writeGreenLed(LOW);
  writeBlueLed(HIGH);

  digitalWrite(MOT1_DIRA, LOW);
  digitalWrite(MOT1_DIRB, HIGH);
  digitalWrite(MOT2_DIRA, HIGH);
  digitalWrite(MOT2_DIRB, LOW);

  Serial.println("SAĞ");
}

void motor_left()
{
  writeRedLed(HIGH);
  writeGreenLed(HIGH);
  writeBlueLed(HIGH);

  digitalWrite(MOT1_DIRA, HIGH);
  digitalWrite(MOT1_DIRB, LOW);
  digitalWrite(MOT2_DIRA, LOW);
  digitalWrite(MOT2_DIRB, HIGH);

  Serial.println("SOL");
}
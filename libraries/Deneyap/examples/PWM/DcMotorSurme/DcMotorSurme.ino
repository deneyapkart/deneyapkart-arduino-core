#include <Arduino.h>

#define PWM_FREQ  5000
#define PWM_RES   8

#define MOT_PIN   D0
#define MOT_DIR1  D4
#define MOT_DIR2  D5

int dutyCycle = 0;
int accAmount = 5;

bool motorDir = true;

void setup() {

  Serial.begin(115200);
  delay(1000);

  pinMode(MOT_DIR1, OUTPUT);
  pinMode(MOT_DIR2, OUTPUT);

  // Yeni ESP32 PWM API
  if (!ledcAttach(MOT_PIN, PWM_FREQ, PWM_RES)) {
    Serial.println("HATA: PWM baslatilamadi!");
    return;
  }

  ledcWrite(MOT_PIN, 0);

  Serial.println();
  Serial.println("======================");
  Serial.println("DC MOTOR SURME TESTI");
  Serial.println("======================");
  Serial.println("Motor ileri yonde basliyor.");


  digitalWrite(MOT_DIR1, LOW);
  digitalWrite(MOT_DIR2, HIGH);
}

void loop() {

  ledcWrite(MOT_PIN, dutyCycle);

  Serial.print("PWM: ");
  Serial.println(dutyCycle);

  dutyCycle += accAmount;

  if (dutyCycle >= 255) {

    dutyCycle = 255;

    Serial.println("Maksimum hiz.");
    Serial.println("Motor yavasliyor...");

    accAmount = -5;
  }

  else if (dutyCycle <= 0) {

    dutyCycle = 0;

    ledcWrite(MOT_PIN, 0);

    Serial.println("Motor durdu.");
    Serial.println("Yon degistiriliyor...");

    delay(500);

    motorDir = !motorDir;

    if (motorDir) {

      digitalWrite(MOT_DIR1, LOW);
      digitalWrite(MOT_DIR2, HIGH);

      Serial.println("Motor ILERI yonde.");

    } else {

      digitalWrite(MOT_DIR1, HIGH);
      digitalWrite(MOT_DIR2, LOW);

      Serial.println("Motor GERI yonde.");
    }

    accAmount = 5;

    Serial.println("Motor hizlaniyor...");
  }

  delay(50);
}
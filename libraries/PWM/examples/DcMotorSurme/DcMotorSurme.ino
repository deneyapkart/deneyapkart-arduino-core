/*
 *  DCMotorSurme örneği,
 *  Bu örnek uygulamada L298N motor sürücü ile dc motor önce hızlanacak daha sonra yavaşlayarak yön değiştirmektedir. 
 *  Bir ileri bir geri olarak döngü içinde bu işlemleri devam ettirmektedir. 
 * 
 */
#define PWM_FREQ  5000                                  // PWM frekansi
#define PWM_CH    0                                     // PWM kanali (0-15)
#define PWM_RES   8                                     // PWM cozunurlugu (1-16 bits)

#define MOT_PIN   PWM0                                  // Deneyap Kart, Deneyap Kart 1A, Deneyap Kart G için Motor PWM pini (PWM0-PWM1) 
//#define MOT_PIN   P0                                  // Deneyap Mini için Motor PWM pini (P0-P1) 
#define MOT_DIR1  D4                                    // Motor yon secme pin1
#define MOT_DIR2  D5                                    // Motor yon secme pin2

uint8_t dutyCycle     = 0;                              // Motor hiz kontrol degiskeni (0-255) (8 bit cozunurluk)
uint8_t accAmount     = 5;                              // Ivmelenme adimi
uint8_t motorDir      = 1;                              // Motor yon secimi 1--> Ileri, 0--> Geri
uint8_t dirCounter    = 0;                              // Yon degisimi icin sayac
uint8_t changeDirFlag = 1;                              // Yon degisim bayragi

void setup() {
  pinMode(MOT_PIN, OUTPUT);                             // Motor PWM pini cikis olarak ayarlandi
  pinMode(MOT_DIR1, OUTPUT);                            // Motor yon secme pin1 cikis olarak ayarlandi
  pinMode(MOT_DIR2, OUTPUT);                            // Motor yon secme pin2 cikis olarak ayarlandi
  
  ledcSetup(PWM_CH, PWM_FREQ, PWM_RES);                 // PWM zamanlayicisi ayarlandi 
  ledcAttachPin(MOT_PIN, PWM_CH);                       // Motor PWM pini ile zamanlayici iliskilendirildi
  Serial.begin(115200);                                 // Seri haberlesme baslatildi
  Serial.println("\nMotor Surme Ornegi");
}

void loop() {
  ledcWrite(PWM_CH, dutyCycle);                         // Motor PWM hiz ayari yapildi

  if(motorDir == 1 && changeDirFlag == 1)               // Ileri yon
  {   
    digitalWrite(MOT_DIR1, LOW);
    digitalWrite(MOT_DIR2, HIGH);    
    changeDirFlag = 0;
    Serial.println("\nMotor ileri yonde hareket ediyor");
  }
  else if(motorDir == 0 && changeDirFlag == 1)          // Geri yon
  {
    digitalWrite(MOT_DIR1, HIGH);
    digitalWrite(MOT_DIR2, LOW);
    changeDirFlag = 0;
    Serial.println("\nMotor geri yonde hareket ediyor");
  }

  if(dutyCycle == 0)
  {
    Serial.println("Hizlaniyor...");  
  }
  if(dutyCycle == 255)  
  {
    Serial.println("Yavasliyor...");  
  } 

  dutyCycle = dutyCycle + accAmount;                    // Motor PWM hiz ayari degistirildi

  if (dutyCycle <= 0 || dutyCycle >= 255)               // Sinir degerlerde motor yon degisimi yapildi
  {
    accAmount = -accAmount;
    dirCounter++;

    if(dirCounter == 2)
    {
      changeDirFlag = 1;
      motorDir      = !motorDir;
      dirCounter    = 0;
    }
  }
  delay(50);                                            
}

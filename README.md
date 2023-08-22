# BLIND CANE
> 2019년도 동계학기 팀 프로젝트

<br/>

### 1

#### 조도센서 Test (1_Cds_sensor_LED)
조도센서를 손으로 가려 어둡게 만들면 LED ON

```
int cds = A0; // 조도센서를 A0핀으로 선언
int led = 4; // LED를 4번핀으로 선언
 
void setup() 
{
   Serial.begin(9600); // 조도센서의 동작 상태를 확인하기 위하여 시리얼 통신을 설정 (전송속도 9600bps)
   pinMode(led, OUTPUT); // LED핀을 OUTPUT으로 설정
}
 
void loop() 
{
   // 조도센서로부터 측정된 밝기 값을 읽어 cdsValue라는 변수에 저장
   // 조도센서로부터 입력되어지는 전압의 크기(0~5V)에 따라 0~1023 범위의 값으로 변환되어 반환
   int cdsValue = analogRead(cds);

   // 측정된 밝기 값을 시리얼 모니터에 출력
   Serial.print("cds =  ");
   Serial.println(cdsValue);
 
  // 조도센서로부터 측정된 밝기 값이 200보다 크다면(어둡다면), 아래의 블록을 실행
   if (cdsValue > 200) 
   {
      digitalWrite(led, HIGH); // LED가 연결된 핀의 로직레벨을 HIGH(5V)로 설정하여, LED ON
      Serial.println("LED ON (cds < 200)"); // 시리얼 모니터에 LED ON (cds < 200) 출력
   }
 
   // 조도센서로부터 측정된 밝기 값이 200보다 작다면(빛을 받는다면), 아래의 블록을 실행
   else 
   {
      digitalWrite(led, LOW); // LED가 연결된 핀의 로직레벨을 LOW(0V)로 설정하여, LED OFF
      Serial.println("LED OFF (cds > 200)"); // 시리얼 모니터에 LED OFF (cds > 200) 출력
   }

   delay(200); // 0.2초 동안 대기
}
```

<br/>

<br/>

### 2

#### 초음파 센서 Test (2_Ultrasonic_sensor)
초음파 센서로부터 10cm 이내로 물체가 감지되었을 때 LED ON

```
int trig = 8; // 초음파 센서의 송신부를 8번핀으로 선언
int echo = 7; // 초음파 센서의 수신부를 9번핀으로 선언
int led = 3; // LED를 3번핀으로 선언
 
void setup() 
{
  Serial.begin(9600); // 초음파 센서의 동작 상태를 확인하기 위하여 시리얼 통신을 설정 (전송속도 9600bps)
  pinMode(trig, OUTPUT); // 초음파 센서의 송신부핀을 OUTPUT으로 설정
  pinMode(echo, INPUT); // 초음파 센서의 수신부핀을 INPUT으로 설정
  pinMode(led, OUTPUT); // LED핀을 OUTPUT으로 설정
}

void loop() 
{
  // 초음파 센서의 송신부핀&수신부핀 모두 초기화 상태
  digitalWrite(trig, LOW);
  digitalWrite(echo, LOW);
  delayMicroseconds(2);

  // 초음파를 쏘기 위한 사전 신호
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
 
  // 초음파가 장애물에 부딪혀서 돌아온 왕복 시간을 측정
  unsigned long duration = pulseIn(echo, HIGH);
 
  // 초음파의 속도는 초당 340미터를 이동하거나, 29마이크로초 당 1센치를 이동합니다.
  // 따라서, 초음파의 이동 거리 = duration(왕복에 걸린시간) / 29 / 2 입니다.
  float distance = duration / 29.0 / 2.0;
 
  // 측정된 거리 값를 시리얼 모니터에 출력
  Serial.print(distance);
  Serial.println("cm");
 
  // 측정된 거리가 10cm 이하라면, 아래의 블록을 실행합니다.
  if (distance < 10) 
  {
    digitalWrite(led, HIGH); // LED가 연결된 핀의 로직레벨을 HIGH(5V)로 설정하여, LED ON
  }

  // 측정된 거리가 10cm 이상이라면, 아래의 블록을 실행합니다.
  else 
  {
    digitalWrite(led, LOW); // LED가 연결된 핀의 로직레벨을 LOW(0V)로 설정하여, LED OFF
  }

  delay(200); // 0.2초 동안 대기
}
```


#### 진동 모터 Test (2_Vibration_motor)
진동 모터가 진동 세기 255로 1초 ON & 3초 STOP

```
int motor = 6; // 진동 모터를 6번핀으로 선언

void setup() 
{
  pinMode(motor, OUTPUT); // 진동 모터핀을 OUTPUT으로 설정
}

void loop() 
{
  // 진동 모터가 진동 세기 255로 1초 ON -> 3초 OFF
  analogWrite(motor, 255);
  delay(1000);
  analogWrite(motor, 0);
  delay(3000);
}
```


#### 피에조 부저 Test (2_Piezo_buzzer)
스위치를 누를 때마다, 피에조 부저에서 '도레미파솔라시' 음계로 소리내기

```
int piezo = 2; // 피에조 부저를 2번핀으로 선언
int sw = 5; // 스위치를 5번핀으로 선언

int numTones = 8; // 음계의 배열을 만들고 배열에 들어가는 인자의 갯수를 8개로 지정
int tones[] = {261, 294, 330, 349, 392, 440, 494, 523}; // 음계는 4옥타브를 기준으로 도, 레, 미, 파, 솔, 라, 시, 도를 출력
 
void setup() 
{
  pinMode(piezo, OUTPUT);  // 피에조 부저핀을 OUTPUT으로 설정
  pinMode(sw, INPUT_PULLUP); // 스위치핀의 모드를 INPUT_PULLUP 상태(초기 로직레벨을 HIGH로 설정)로 설정
}
 
void loop() 
{
  // 스위치가 연결된 핀의 로직레벨이 LOW라면(버튼이 눌렸다면)
  if (digitalRead(sw) == LOW) 
  {
    for (int i = 0; i < numTones; i++) 
    {
      //numTones(8)의 수만큼 반복 실행합니다.
      // tone함수를 통해 피에조부저에서 소리가 나며 tones[]배열에 있는 주파수에 해당하는 음계가 출력
      tone(piezo, tones[i]);

      delay(500); // 0.5초 동안 대기
    }

    noTone(piezo); // 피에조 부저가 연결된 핀으로부터 square-ware를 생성을 중단하도록 설정
  }
}
```


#### 초음파 센서 & 진동 모터 & 피에조 부저 Test (2_Ultrasonic_sensor_Vibration_motor_Piezo_buzzer)
초음파 센서로부터 50cm 이내로 물체가 감지되었을 때

진동 모터가 진동 세기 255로 ON&피에조 부저가 5옥타브 라음으로 0.1초간 ON

```
int motor = 6; // 진동 모터를 6번핀으로 선언
int piezo = 2; // 피에조 부저를 2번핀으로 선언
int trig = 8; // 초음파 센서의 송신부를 8번핀으로 선언
int echo = 7; // 초음파 센서의 수신부를 9번핀으로 선언

void setup() 
{
  Serial.begin(9600); // 초음파 센서의 동작 상태를 확인하기 위하여 시리얼 통신을 설정 (전송속도 9600bps)
  pinMode(motor, OUTPUT); // 진동 모터핀을 OUTPUT으로 설정
  pinMode(piezo, OUTPUT);  // 피에조 부저핀을 OUTPUT으로 설정
  pinMode(trig, OUTPUT); // 초음파 센서의 송신부핀을 OUTPUT으로 설정
  pinMode(echo, INPUT); // 초음파 센서의 수신부핀을 INPUT으로 설정
}

void loop() 
{
  // 초음파 센서의 송신부핀&수신부핀 모두 초기화 상태
  digitalWrite(trig, LOW);
  digitalWrite(echo, LOW);
  delayMicroseconds(2);

  // 초음파를 쏘기 위한 사전 신호
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
 
  // 초음파가 장애물에 부딪혀서 돌아온 왕복 시간을 측정
  unsigned long duration = pulseIn(echo, HIGH);
 
  // 초음파의 속도는 초당 340미터를 이동하거나, 29마이크로초 당 1센치를 이동합니다.
  // 따라서, 초음파의 이동 거리 = duration(왕복에 걸린시간) / 29 / 2 입니다.
  float distance = duration / 29.0 / 2.0;
 
  // 측정된 거리 값를 시리얼 모니터에 출력
  Serial.print(distance);
  Serial.println("cm");
 
  // 측정된 거리가 50cm 미만이라면, 아래의 블록을 실행합니다.
  if (distance < 50) 
  {
    analogWrite(motor, 255); // 진동 모터가 진동 세기 255로 ON
    tone(piezo,880,100); // 피에조 부저가 5옥타브 라음으로 0.1초간 ON
    delay(100); // 0.1초 동안 대기
    noTone(piezo); // 피에조 부저가 연결된 핀으로부터 square-ware를 생성을 중단하도록 설정
  }

  // 측정된 거리가 50cm 이상이라면, 아래의 블록을 실행합니다.
  else 
  {
    analogWrite(motor, 0); // 진동 모터가 OFF
  }

  delay(200); // 0.2초 동안 대기합니다.
}
```

<br/>

<br/>

### 3

#### RFID Test (3_RFID)
RFID 카드 정보 읽기

```
#include <SPI.h>
#include <MFRC522.h>

// 나머지 PIN은 SPI 라이브러리를 사용하기에 별도의 설정이 필요없다.
#define RST_PIN 9 // RST(Reset)을 9번핀으로 선언
#define SS_PIN 10 // SPI 통신을 위한 SS(Chip Select)를 10번핀으로 선언

MFRC522 rfid(SS_PIN, RST_PIN); // MFRC522를 이용하기 위해 rfid 이름으로 클래스 객체 생성

MFRC522::MIFARE_Key key; 

byte nuidPICC[4]; // 카드 ID들을 저장(비교)하기 위한 배열(변수) 선언

void setup() 
{ 
  Serial.begin(9600); // RFID의 동작 상태를 확인하기 위하여 시리얼 통신을 설정 (전송속도 9600bps)
  SPI.begin(); // SPI 통신 시작 (SPI : 하나의 마스터와 다수의 SLAVE(종속적인 역할)간의 통신 방식)
  rfid.PCD_Init(); // RFID(MFRC522) 초기화

  //초기 키 ID 초기화
  for (byte i = 0; i < 6; i++) 
  {
    key.keyByte[i] = 0xFF;
  }
  
  // MIFARE 타입의 카드키 종류들만 인식됨을 표시
  Serial.println(F("This code scan the MIFARE Classsic NUID."));
  Serial.print(F("Using the following key:"));
  printHex(key.keyByte, MFRC522::MF_KEY_SIZE);
}
 
void loop() 
{
  // 새로운 카드가 인식되었다면 다음으로 넘어가고 아니면 더이상 실행 안하고 리턴
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // ID가 읽혀졌다면 다음으로 넘어가고 아니면 더이상 실행 안하고 리턴
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  // 현재 접촉되는 카드 타입을 읽어와 시리얼 모니터에 출력
  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  // MIFARE 방식의 카드인지 확인하고 아니면 리턴
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI && piccType != MFRC522::PICC_TYPE_MIFARE_1K && piccType != MFRC522::PICC_TYPE_MIFARE_4K) 
  {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  // 만약 바로 전에 인식한 RF 카드와 다른 혹은 새로운 카드가 인식되면
  if (rfid.uid.uidByte[0] != nuidPICC[0] || rfid.uid.uidByte[1] != nuidPICC[1] || rfid.uid.uidByte[2] != nuidPICC[2] || rfid.uid.uidByte[3] != nuidPICC[3] ) 
  {
    Serial.println(F("A new card has been detected."));

    // 고유 ID를 저장    
    for (byte i = 0; i < 4; i++) 
    {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }
   
    // 저장한 고유 ID를 16진수로 변환해서 시리얼 모니터에 출력
    Serial.println(F("The NUID tag is:"));
    Serial.print(F("In hex: "));
    printHex(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();

    // 16진수로 변환한 고유 ID를 10진수로 변환해서 시리얼 모니터에 출력
    Serial.print(F("In dec: "));
    printDec(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
  }

  else Serial.println(F("Card read previously.")); // 바로 전에 인식한 카드와 동일하다면 다른 처리 없이 "이미 인식된 카드"라는 메세지를 출력
  rfid.PICC_HaltA(); // PICC 종료
  rfid.PCD_StopCrypto1(); // 암호화 종료(?)

  // 다시 처음으로 돌아감.
}

// 16진수로 변환하는 함수
void printHex(byte *buffer, byte bufferSize) 
{
  for (byte i = 0; i < bufferSize; i++) 
  {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

// 10진수로 변환하는 함수
void printDec(byte *buffer, byte bufferSize) 
{
  for (byte i = 0; i < bufferSize; i++) 
  {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}
```

#### RFID & 피에조 부저 Test (3_RFID_Piezo_buzzer)
RFID 카드 ID가 지정된 ID일 경우 피에조 부저가 4옥타브 라음으로 0.1초간 ON

RFID 카드 ID가 지정된 ID가 아닌 경우 피에조 부저가 4옥타브 라음으로 0.1초간 두번 ON

```
#include <SPI.h>
#include <MFRC522.h>

// 나머지 PIN은 SPI 라이브러리를 사용하기에 별도의 설정이 필요없다.
#define RST_PIN 9 // RST(Reset)을 9번핀으로 선언
#define SS_PIN 10 // SPI 통신을 위한 SS(Chip Select)를 10번핀으로 선언

MFRC522 rfid(SS_PIN, RST_PIN); // MFRC522를 이용하기 위해 rfid 이름으로 클래스 객체 생성

int piezo = 2; // 피에조 부저를 2번핀으로 선언

void setup() 
{
  Serial.begin(9600); // RFID의 동작 상태를 확인하기 위하여 시리얼 통신을 설정 (전송속도 9600bps)
  SPI.begin(); // SPI 통신 시작 (SPI : 하나의 마스터와 다수의 SLAVE(종속적인 역할)간의 통신 방식)
  rfid.PCD_Init(); // RFID(MFRC522) 초기화

  pinMode(piezo, OUTPUT);  // 피에조 부저핀을 OUTPUT으로 설정
}

void loop() 
{
  //  태그 접촉이 되지 않았을 때 또는 ID가 읽혀지지 않았을 때 return
  if ( ! rfid.PICC_IsNewCardPresent() || ! rfid.PICC_ReadCardSerial() ) 
  {
    delay(500); // 0.5초 동안 대기
    return; // return
  }
  
  //카드번호 찾아서 기록 
  if(rfid.uid.uidByte[0] == 244 && rfid.uid.uidByte[1] == 181 && rfid.uid.uidByte[2] == 249 && rfid.uid.uidByte[3] == 233) 
  { 
    // 2번 태그 ID가 맞을 경우  
    Serial.println("OK"); // 시리얼 모니터에 "OK" 출력
    tone(piezo,440,100); // 피에조 부저가 4옥타브 라음으로 0.1초간 ON
    delay(100); // 0.1초 동안 대기
    noTone(piezo); // 피에조 부저가 연결된 핀으로부터 square-ware를 생성을 중단하도록 설정
  }
  
  // 다른 태그 ID일 경우
  else 
  {
    Serial.println("Who are you?"); // 시리얼 모니터에 "Who are you?" 출력 
    tone(piezo,880,100); // 피에조 부저가 4옥타브 라음으로 0.1초간 ON
    delay(100); // 0.1초 동안 대기
    tone(piezo,880,100); // 피에조 부저가 4옥타브 라음으로 0.1초간 ON
    delay(100); // 0.1초 동안 대기
    noTone(piezo); // 피에조 부저가 연결된 핀으로부터 square-ware를 생성을 중단하도록 설정
  }  
}
```

<br/>

<br/>

### 4

#### 최종본 (4_Total)
최종본

```
#include <SPI.h>
#include <MFRC522.h>

// 나머지 PIN은 SPI 라이브러리를 사용하기에 별도의 설정이 필요없다.
#define RST_PIN 9 // RST(Reset)을 9번핀으로 선언
#define SS_PIN 10 // SPI 통신을 위한 SS(Chip Select)를 10번핀으로 선언

MFRC522 rfid(SS_PIN, RST_PIN); // MFRC522를 이용하기 위해 rfid 이름으로 클래스 객체 생성

int cds = A0; // 조도센서를 A0핀으로 선언
int led = 4; // LED를 4번핀으로 선언

int motor = 6; // 진동 모터를 6번핀으로 선언
int piezo = 2; // 피에조 부저를 2번핀으로 선언
int trig = 8; // 초음파 센서의 송신부를 8번핀으로 선언
int echo = 7; // 초음파 센서의 수신부를 9번핀으로 선언

void setup() 
{
  Serial.begin(9600);
  
  pinMode(led, OUTPUT); // LED핀을 OUTPUT으로 설정

  pinMode(motor, OUTPUT); // 진동 모터핀을 OUTPUT으로 설정
  pinMode(piezo, OUTPUT);  // 피에조 부저핀을 OUTPUT으로 설정
  pinMode(trig, OUTPUT); // 초음파 센서의 송신부핀을 OUTPUT으로 설정
  pinMode(echo, INPUT); // 초음파 센서의 수신부핀을 INPUT으로 설정

  SPI.begin(); // SPI 통신 시작 (SPI : 하나의 마스터와 다수의 SLAVE(종속적인 역할)간의 통신 방식)
  rfid.PCD_Init(); // RFID(MFRC522) 초기화
}

void loop() 
{
  CdsSensorLED();
  UltrasonicSensorVibrationMotorPiezoBuzzer();
  RFIDPiezoBuzzer();
}

void CdsSensorLED()
{
  // 조도센서로부터 측정된 밝기 값을 읽어 cdsValue라는 변수에 저장
  // 조도센서로부터 입력되어지는 전압의 크기(0~5V)에 따라 0~1023 범위의 값으로 변환되어 반환
  int cdsValue = analogRead(cds);

  // 측정된 밝기 값을 시리얼 모니터에 출력
  Serial.print("cds =  ");
  Serial.println(cdsValue);
 
  // 조도센서로부터 측정된 밝기 값이 200보다 크다면(어둡다면), 아래의 블록을 실행
  if (cdsValue > 200) 
  {
    digitalWrite(led, HIGH); // LED가 연결된 핀의 로직레벨을 HIGH(5V)로 설정하여, LED ON
    Serial.println("LED ON (cds < 200)"); // 시리얼 모니터에 LED ON (cds < 200) 출력
  }
 
  // 조도센서로부터 측정된 밝기 값이 200보다 작다면(빛을 받는다면), 아래의 블록을 실행
  else 
  {  
    digitalWrite(led, LOW); // LED가 연결된 핀의 로직레벨을 LOW(0V)로 설정하여, LED OFF
    Serial.println("LED OFF (cds > 200)"); // 시리얼 모니터에 LED OFF (cds > 200) 출력
  }

  delay(200); // 0.2초 동안 대기
}

void UltrasonicSensorVibrationMotorPiezoBuzzer()
{
  // 초음파 센서의 송신부핀&수신부핀 모두 초기화 상태
  digitalWrite(trig, LOW);
  digitalWrite(echo, LOW);
  delayMicroseconds(2);

  // 초음파를 쏘기 위한 사전 신호
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
 
  // 초음파가 장애물에 부딪혀서 돌아온 왕복 시간을 측정
  unsigned long duration = pulseIn(echo, HIGH);
 
  // 초음파의 속도는 초당 340미터를 이동하거나, 29마이크로초 당 1센치를 이동합니다.
  // 따라서, 초음파의 이동 거리 = duration(왕복에 걸린시간) / 29 / 2 입니다.
  float distance = duration / 29.0 / 2.0;
 
  // 측정된 거리 값를 시리얼 모니터에 출력
  Serial.print(distance);
  Serial.println("cm");
 
  // 측정된 거리가 50cm 미만이라면, 아래의 블록을 실행합니다.
  if (distance < 50) 
  {
    analogWrite(motor, 255); // 진동 모터가 진동 세기 255로 ON
    tone(piezo,523,100); // 피에조 부저가 도음으로 100박자(음길이)간 ON           
    delay(300); // 0.3초 동안 대기
    tone(piezo,523,100); // 피에조 부저가 도음으로 100박자(음길이)간 ON
    delay(500); // 0.5초 동안 대기
    noTone(piezo); // 피에조 부저가 연결된 핀으로부터 square-ware를 생성을 중단하도록 설정
  }

  // 측정된 거리가 50cm 이상이라면, 아래의 블록을 실행합니다.
  else 
  {
    analogWrite(motor, 0); // 진동 모터가 OFF
  }

  delay(200); // 0.2초 동안 대기합니다.
}

void RFIDPiezoBuzzer()
{
  //  태그 접촉이 되지 않았을 때 또는 ID가 읽혀지지 않았을 때 return
  if ( ! rfid.PICC_IsNewCardPresent() || ! rfid.PICC_ReadCardSerial() ) 
  {
    delay(500); // 0.5초 동안 대기
    return; // return
  }
  
  //카드번호 찾아서 기록 
  if(rfid.uid.uidByte[0] == 244 && rfid.uid.uidByte[1] == 181 && rfid.uid.uidByte[2] == 249 && rfid.uid.uidByte[3] == 233) 
  { 
    // 2번 태그 ID가 맞을 경우  
    Serial.println("OK"); // 시리얼 모니터에 "OK" 출력
    tone(piezo,440,100); // 피에조 부저가 4옥타브 라음으로 0.1초간 ON
    delay(100); // 0.1초 동안 대기
    noTone(piezo); // 피에조 부저가 연결된 핀으로부터 square-ware를 생성을 중단하도록 설정
  }
  
  // 다른 태그 ID일 경우
  else 
  {
    Serial.println("Who are you?"); // 시리얼 모니터에 "Who are you?" 출력 
    tone(piezo,880,100); // 피에조 부저가 4옥타브 라음으로 0.1초간 ON
    delay(100); // 0.1초 동안 대기
    tone(piezo,880,100); // 피에조 부저가 4옥타브 라음으로 0.1초간 ON
    delay(100); // 0.1초 동안 대기
    noTone(piezo); // 피에조 부저가 연결된 핀으로부터 square-ware를 생성을 중단하도록 설정
  }
}
```

<br/>

<br/>

### 5

#### 납땜

<br/>

<br/>

### 6

#### 하드웨어 제작

<br/>

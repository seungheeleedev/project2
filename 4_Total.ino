/*
   제목 : 4_Total
   내용 : 최종본
*/


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
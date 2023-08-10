/*
   제목 : 3_RFID_Piezo_buzzer
   내용 : RFID 카드 ID가 지정된 ID일 경우 피에조 부저가 4옥타브 라음으로 0.1초간 ON & 지정된 ID가 아닌 경우 피에조 부저가 4옥타브 라음으로 0.1초간 두번 ON
*/


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
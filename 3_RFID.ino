/*
   제목 : 3_RFID
   내용 : RFID 카드 정보 읽기
*/


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
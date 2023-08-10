/*
   제목 : 1_Cds_sensor_LED
   내용 : 조도센서는 빛의 밝기에 대하여 전기적인 성질로 변환시켜주는 센서
         조도센서를 손으로 가려 어둡게 만들면 LED ON
*/


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
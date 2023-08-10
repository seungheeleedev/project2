/*
   제목 : 2_Ultrasonic_sensor
   내용 : 초음파 센서로부터 10cm 이내로 물체가 감지되었을 때 LED ON
*/


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
/*
   제목 : 2_Ultrasonic_sensor_Vibration_motor_Piezo_buzzer
   내용 : 초음파 센서로부터 50cm 이내로 물체가 감지되었을 때 진동 모터가 진동 세기 255로 ON&피에조 부저가 5옥타브 라음으로 0.1초간 ON
*/

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
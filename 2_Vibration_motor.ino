/*
   제목 : 2_Vibration_motor
   내용 : 진동 모터가 진동 세기 255로 1초 ON & 3초 STOP
*/


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
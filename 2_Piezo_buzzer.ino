/*
   제목 : 2_Piezo_buzzer
   내용 : 스위치를 누를 때마다, 피에조 부저에서 '도레미파솔라시' 음계로 소리내기
*/


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

/*
 예제 7.2
 서보모터 구동
*/
 
// 서보모터 라이브러리 불러오기
#include <Servo.h> 

// 서보모터 이름 설정
Servo motor1; 

// 서보 모터 신호핀 설정
int servoMotorPin = 9;
int tact1 = 2;
int tact2 = 3;
// 포텐쇼미터 핀 설정
int potentioMeterPin = 0;

// 모터 각도 변수 설정
int motorAngle;
int motorAngleOld;

void setup() {
  pinMode(tact1,INPUT_PULLUP);
  pinMode(tact2, INPUT_PULLUP);
  // 서보모터 설정. 0.6ms 부터 2.4ms 범위로 설정
  motor1.attach(servoMotorPin,600,2400);
  motorAngle = 90;
  motor1.write(motorAngle);

  // 시리얼 통신 설정  
  Serial.begin(9600);
}

void loop(){
  // 포텐쇼미터 값을 읽어옴
  if(digitalRead(tact1) == LOW)
  {
    for(int i = motorAngle; i>=0; i-- )
    {
       motor1.write(i);
       motorAngle = i;
       delayMicroseconds(4500);
       if(digitalRead(tact2) == LOW)
        break;
    }
  }
  // 포텐쇼미터 값을 모터 각도로 변환한다
  if(digitalRead(tact2) == LOW)
  {
    for(int i = motorAngle; i<=180; i++ )
    {
       motor1.write(i);
       motorAngle = i;
       delayMicroseconds(4500);
       if(digitalRead(tact1) == LOW)
        break;
    }
  }

  // 이전각도와 현재 각도가 같지 않으면 시리얼 모니터에 각도를 출력한다.  
  if(motorAngle != motorAngleOld){
    Serial.print("Servo Motor Angle is: ");
    Serial.println(motorAngle);
  }

  // 현재의 모터 각도를 저장한다.
  motorAngleOld = motorAngle;
  
  delay(20);

}

/*
 예제 2.3
 컴퓨터로부터 시리얼 통신을 통하여 데이터 수신하기
*/

// LED 출력을 할 핀 번호 설정

// 점멸횟수 변수 설정
int blinkNumber =0;

String stringValue[]={"Binay : ","Octal : "}; // array

void setup() {
  // 9600bps로 시리얼 통신 설정  
  Serial.begin(9600);
}

void loop() {
// 시리얼 통신으로 입력 받은 데이터가 있는지를 검사하여
// 데이터가 있을 경우에 if문 안의 명령어를 실행
  if(Serial.available()){       
  // val 변수에 시리얼 통신값 읽어오기
    char val = Serial.read();
    // 입력된 값이 0~9의 숫자인지를 판단
    if(isDigit(val)){
     // val은 ASCII 코드값이므로 숫자로 바꿔주기 위하여 
     // '0'의 아스키 코드값을 빼줌
     // blinkNumber에는 실제 숫자가 저장된다.
     blinkNumber = (val - '0');
    }
  }

if(blinkNumber != 0)//blinkNumber == 0 일 경우에도 계속하여 출력이 되어져서 추가하였음.
{
  Serial.println();
  // 'char Value'를 출력하고 문자열과 숫자를 변수 유형별로 출력한다.
  Serial.print("Number = ");
  Serial.print(blinkNumber);
  Serial.print(", ");
  Serial.print(stringValue[0]);  // stringValue 중 첫 번째 문자열 출력
  Serial.print(blinkNumber,BIN); // 2진수 형태로 출력
  Serial.print(", ");
  Serial.print(stringValue[1]);  // stringValue 중 첫 번째 문자열 출력
  Serial.print(blinkNumber,OCT); // 16진수 형태로 출력
  // 줄바꿈
  Serial.println();
}


  // 점멸 횟수를 리셋함
  blinkNumber = 0;
}

//코드 합치기

#include <Adafruit_NeoPixel.h>            //네오픽셀을 사용하기 위한 라이브러리

//초음파 센서(보행자 감지)
int trig = 13;
int echo = 12;
//초음파 센서2(자동차 감지)
int trig2 = 11;
int echo2 = 10;
//적외선 센서(자동차 감지)
int out = 9;
//RGB LED(보행자 신호등)
int LED_R = 6;      //LED RED
int LED_G = 7;     //LED GREEN
int LED_B = 8;     //LED BLUE
//네오 픽셀
int neo1 = 3;       //인도 위의 네오픽셀 제어
int neo2 = 4;       //자동차 신호등(네오픽셀) 제어
int neo3 = 5;       //도로 위의 네오픽셀 제어
//부저
int buzzer = 2;

int duration;
int distance;

//buzzer 음계
int mel_doreme[10] = {262, 294, 330, 349, 392, 440, 494, 523, 587, 659};   //도레미파솔라시도레(보행자 신호 초록불일 때 사용)

//////*네오픽셀 사용하기*//////
//네오픽셀을 사용하기 위해 객체 하나를 생성한다. 
//첫번째 인자값은 네오픽셀의 LED의 개수
//두번째 인자값은 네오픽셀이 연결된 아두이노의 핀번호
//세번째 인자값은 네오픽셀의 타입에 따라 바뀌는 flag
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(9, neo1, NEO_GRB + NEO_KHZ800);   //인도 위의 네오픽셀
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(3, neo2, NEO_GRB + NEO_KHZ800);   //자동차 신호등(네오픽셀)
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(14, neo3, NEO_GRB + NEO_KHZ800);  //도로 위의 네오픽셀



void setup() {
  pinMode(trig, OUTPUT);        //초음파 센서 trig
  pinMode(echo, INPUT);         //초음파 센서 echo
  pinMode(trig2, OUTPUT);        //초음파 센서 trig2
  pinMode(echo2, INPUT);         //초음파 센서 echo2
  pinMode(LED_R, OUTPUT);       //LED
  pinMode(LED_G, OUTPUT);       //LED
  pinMode(LED_B, OUTPUT);       //LED
  pinMode(out, INPUT);          //적외선 센서
  //네오픽셀
  strip1.begin(); //네오픽셀1을 초기화하기 위해 모든LED를 off시킨다
  strip1.show();
  strip2.begin(); //네오픽셀2를 초기화하기 위해 모든LED를 off시킨다
  strip2.show(); 
  strip3.begin(); //네오픽셀3를 초기화하기 위해 모든LED를 off시킨다
  strip3.show(); 

  //test
 //Serial.begin(9600);
  
}

void loop() {
  //초음파 센서 - 보행자 감지
  digitalWrite(trig, HIGH);             //0.01초만큼 초음파 발사
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration * 0.017;      //cm 단위로 변환

  //초음파 센서2 - 자동차 감지
  digitalWrite(trig2, HIGH);             //0.01초만큼 초음파 발사
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);

  int duration2 = pulseIn(echo2, HIGH);
  int distance2 = duration * 0.017;      //cm 단위로 변환

  if(distance < 20 ){                   //보행자1이 인식되면(초음파 센서로 인식한 거리<20)
  /*TEST
   * digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    //0.5초 단위로 distance를 나타낼 수 있도록 Serial.println하기
    Serial.print(distance2);
    Serial.println("cm");
    delay(500);
   */
   //네오픽셀
   strip1.begin(); //네오픽셀1을 초기화하기 위해 모든LED를 off시킨다
   strip1.show();
   strip2.begin(); //네오픽셀2를 초기화하기 위해 모든LED를 off시킨다
   strip2.show(); 
   strip3.begin(); //네오픽셀3를 초기화하기 위해 모든LED를 off시킨다
   strip3.show(); 




   
    //적외선 센서로 자동차 감지
      if(digitalRead(out) == LOW || distance2 < 10){       //적외선 센서의 값을 읽어옴, LOW -> 장애물 감지가 될 때
        delay(5000);                            //자동차가 감지되면 5초 후에
        /*TEST
        digitalWrite(LED_R, HIGH);
        delay(1000);
        digitalWrite(LED_R, LOW);
        */
      }
      else{                                   //장애물 감지가 안될 때
         delay(2000);                         //자동차가 감지되지 않으면 2초 후에
         /*TEST
         digitalWrite(LED_B, HIGH);
         delay(1000);
         digitalWrite(LED_B, LOW);
         */
      }
      //자동차 신호: 초 -> 노 -> 빨
      ///green
      strip2.setPixelColor(2,strip2.Color(0, 225, 0));
      strip2.show();
      delay(1000);
      strip2.setPixelColor(2,strip2.Color(0, 0, 0));
      //yellow
      strip2.setPixelColor(1,strip2.Color(255, 228, 0));
      strip2.show();
      delay(1000);
      strip2.setPixelColor(1,strip2.Color(0, 0, 0));
      //red
      strip2.setPixelColor(0,strip2.Color(255, 0, 0));
      strip2.show();
      delay(1000);
      strip2.setPixelColor(0,strip2.Color(0, 0, 0));
      //보행자 신호: 빨 -> 초
      digitalWrite(LED_R, LOW);               //보행자 신호: 빨간불 OFF
      digitalWrite(LED_G, HIGH);              //보행자 신호: 초록불 ON

      //도로 위의 네오픽셀 : 무지개/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      for(uint16_t j=0; j<256; j++) {
        for(uint16_t i=0; i<strip3.numPixels(); i++) {
          strip3.setPixelColor(i, Wheel((i+j) & 255));
        }
        strip3.show();
        delay(10);
      }
      
      //보행자1이 횡단보도를 건너는 중에
      //인도 위의 네오픽셀 제어(초록색 LED가 하나씩 줄면서 신호가 남은 시간 표시)
      //네오픽셀: 초록색이 9개에서 0개로 2초마다 1개씩 줄어든다
      //9~12초(LED가 4~2개 남았을 때)에 보행자2가 인식되면 7초(LED가 5개 남았을 때)로 돌아감
      
      
      //초록색 0~8번 켜짐
      for(uint16_t i=0;i<9;i++){
        strip1.setPixelColor(i,strip1.Color(0,255,0));
      }
      if(digitalRead(out) == LOW){                    //자동차가 인식되면
        for(int n=0;n<2;n++){
          for(uint16_t j=0;j<14;j++){
            strip3.setPixelColor(j,strip3.Color(255,0,0));
          }
          strip3.show();
          tone(buzzer, 1175, 400);
          delay(400);
          noTone(8);
          
          for(uint16_t j=0;j<14;j++){
            strip3.setPixelColor(j,strip3.Color(0,0,0));
          }
          strip3.show();

          for(uint16_t j=0;j<14;j++){
            strip3.setPixelColor(j,strip3.Color(255,0,0));
          }
          strip3.show();
          tone(buzzer, 587, 600);
          delay(600);
          noTone(8);
          for(uint16_t j=0;j<14;j++){
            strip3.setPixelColor(j,strip3.Color(0,0,0));
          }
          strip3.show();
        }
      }

      else{
        strip1.show();
        tone(buzzer, mel_doreme[0], 2000);                //mel_doreme[0]을 2초간 연주
        delay(2000);
      }
      
      //보행자 신호 = 2초
      
      //초록색 0~4 번(3~8초) 2초에 1개씩 꺼짐
      for(uint16_t i=0; i<4; i++) {
        strip1.setPixelColor(i, strip1.Color(0,0,0));
        if(digitalRead(out) == LOW){                    //자동차가 인식되면
        for(int n=0;n<2;n++){
          for(uint16_t j=0;j<14;j++){
            strip3.setPixelColor(j,strip3.Color(255,0,0));
          }
          strip3.show();
          tone(buzzer, 1175, 400);
          delay(400);
          noTone(8);

          for(uint16_t j=0;j<14;j++){
            strip3.setPixelColor(j,strip3.Color(0,0,0));
          }
          strip3.show();

          for(uint16_t j=0;j<14;j++){
            strip3.setPixelColor(j,strip3.Color(255,0,0));
          }
          strip3.show();
          tone(buzzer, 587, 600);
          delay(600);
          noTone(8);
          for(uint16_t j=0;j<14;j++){
            strip3.setPixelColor(j,strip3.Color(0,0,0));
          }
          strip3.show();
        }
      }
      else{
        strip1.show();
        tone(buzzer, mel_doreme[i+1], 2000);                //mel_doreme[i+1]을 2초간 연주
        delay(2000);
      }
        
      }
      //보행자 신호 = 8초
      
      //초록색 5~6번(9~12초) 에 보행자2가 인식되면
      for(uint16_t i=4; i<6; i++) {
        
        //초음파 센서 - 보행자 감지
        digitalWrite(trig, HIGH);             //0.01초만큼 초음파 발사
        delayMicroseconds(10);
        digitalWrite(trig, LOW);
  
        duration = pulseIn(echo, HIGH);
        distance = duration * 0.017;      //cm 단위로 변환
        /*test
        Serial.print(distance);
        Serial.println("cm");
        */
        
        if(distance < 20){
          for(uint16_t i=3;i<9;i++){
            strip1.setPixelColor(i,strip1.Color(0,255,0));
          }
          if(digitalRead(out) == LOW){                    //자동차가 인식되면
        for(int n=0;n<2;n++){
          for(uint16_t j=0;j<14;j++){
            strip3.setPixelColor(j,strip3.Color(255,0,0));
          }
          strip3.show();
          tone(buzzer, 1175, 400);
          delay(400);
          noTone(8);
          for(uint16_t j=0;j<14;j++){
            strip3.setPixelColor(j,strip3.Color(0,0,0));
          }
          strip3.show();

          for(uint16_t j=0;j<14;j++){
            strip3.setPixelColor(j,strip3.Color(255,0,0));
          }
          strip3.show();
          tone(buzzer, 587, 600);
          delay(600);
          noTone(8);
          for(uint16_t j=0;j<14;j++){
            strip3.setPixelColor(j,strip3.Color(0,0,0));
          }
          strip3.show();
        }
      }
          else{
            strip1.show();
            tone(buzzer, mel_doreme[3], 2000);                //mel_doreme[3]을 2초간 연주
            delay(2000);     
          }
          
          for(uint16_t i=3; i<6; i++) {
            strip1.setPixelColor(i, strip1.Color(0,0,0));
            if(digitalRead(out) == LOW){                    //자동차가 인식되면
        for(int n=0;n<2;n++){
          for(uint16_t j=0;j<14;j++){
            strip3.setPixelColor(j,strip3.Color(255,0,0));
          }
          strip3.show();
          tone(buzzer, 1175, 400);
          delay(400);
          noTone(8);
          for(uint16_t j=0;j<14;j++){
            strip3.setPixelColor(j,strip3.Color(0,0,0));
          }
          strip3.show();

          for(uint16_t j=0;j<14;j++){
            strip3.setPixelColor(j,strip3.Color(255,0,0));
          }
          strip3.show();
          tone(buzzer, 587, 600);
          delay(600);
          noTone(8);
          for(uint16_t j=0;j<14;j++){
            strip3.setPixelColor(j,strip3.Color(0,0,0));
          }
          strip3.show();
        }
      }
            else{
              strip1.show();
              tone(buzzer, mel_doreme[i+1], 2000);                //mel_doreme[i+1]을 2초간 연주
              delay(2000);
            }
            
          }
          break;
        }
        
        strip1.setPixelColor(i, strip1.Color(0,0,0));
        if(digitalRead(out) == LOW){                    //자동차가 인식되면
        for(int n=0;n<2;n++){
          for(uint16_t j=0;j<14;j++){
            strip3.setPixelColor(j,strip3.Color(255,0,0));
          }
          strip3.show();
          tone(buzzer, 1175, 400);
          delay(400);
          noTone(8);
          for(uint16_t j=0;j<14;j++){
            strip3.setPixelColor(j,strip3.Color(0,0,0));
          }
          strip3.show();

          for(uint16_t j=0;j<14;j++){
            strip3.setPixelColor(j,strip3.Color(255,0,0));
          }
          strip3.show();
          tone(buzzer, 587, 600);
          delay(600);
          noTone(8);
          for(uint16_t j=0;j<14;j++){
            strip3.setPixelColor(j,strip3.Color(0,0,0));
          }
          strip3.show();
        }
      }
      else{
        strip1.show();
        tone(buzzer, mel_doreme[i+1], 2000);                //mel_doreme[i+1]을 2초간 연주
        delay(2000);
      }
        
      }
      //보행자 신호 = 12초

      for(uint16_t i=6; i<strip1.numPixels(); i++) {
        strip1.setPixelColor(i, strip1.Color(0,0,0));
        if(digitalRead(out) == LOW){                    //자동차가 인식되면
        for(int n=0;n<2;n++){
          for(uint16_t j=0;j<14;j++){
            strip3.setPixelColor(j,strip3.Color(255,0,0));
          }
          strip3.show();
          tone(buzzer, 1175, 400);
          delay(400);
          noTone(8);
          for(uint16_t j=0;j<14;j++){
            strip3.setPixelColor(j,strip3.Color(0,0,0));
          }
          strip3.show();

          for(uint16_t j=0;j<14;j++){
            strip3.setPixelColor(j,strip3.Color(255,0,0));
          }
          strip3.show();
          tone(buzzer, 587, 600);
          delay(600);
          noTone(8);
          for(uint16_t j=0;j<14;j++){
            strip3.setPixelColor(j,strip3.Color(0,0,0));
          }
          strip3.show();
        }
      }
      else{
        strip1.show();
        tone(buzzer, mel_doreme[i+1], 2000);                //mel_doreme[i+1]을 2초간 연주
        delay(2000);
      }
        
      }

      


      
  
  }//if end
  else{                       //보행자가 인식되지 않았을 때의 상태
    //보행자 신호: 빨간불
    digitalWrite(LED_G, LOW);                 //초록불 OFF
    digitalWrite(LED_R, HIGH);                //빨간불 ON
    //자동차 신호: 초록불
    strip2.setPixelColor(2,strip2.Color(0, 225, 0));    //green : ON
    strip2.setPixelColor(1,strip2.Color(0, 0, 0));      //yellow : OFF
    strip2.setPixelColor(0,strip2.Color(0, 0, 0));      //red : OFF
    strip2.show();

    //네오픽셀: 빨간색 0~9번 다 켜짐
      for(uint16_t i=0;i<9;i++){
        strip1.setPixelColor(i,strip1.Color(255,0,0));
      }
      strip1.show();
  }//else end

  
  
} //end of void loop()

//255가지의 색을 나타내는 함수
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip3.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip3.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip3.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

/*car_light
void carLight_GtoR(uint8_t wait){
  //green
  strip2.setPixelColor(2,strip2.Color(0, 225, 0));
  strip2.show();
  delay(wait);
  strip2.setPixelColor(2,strip2.Color(0, 0, 0));
  //yellow
  strip2.setPixelColor(1,strip2.Color(255, 228, 0));
  strip2.show();
  delay(wait);
  strip2.setPixelColor(1,strip2.Color(0, 0, 0));
  //red
  strip2.setPixelColor(0,strip2.Color(255, 0, 0));
  strip2.show();
  delay(wait);
  strip2.setPixelColor(0,strip22.Color(0, 0, 0));
}
*/


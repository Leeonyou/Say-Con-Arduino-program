#include <SoftwareSerial.h> // 0,1번핀 제외하고 Serial 통신을 하기 위해 선언
#include <Keyboard.h>
#include <Mouse.h>
// Serial 통신핀으로 D11번핀을 Rx로, D10번핀을 Tx로 선언








void setup()
{
 Serial.begin(9600); // 통신 속도 9600bps로 PC와 시리얼 통신 시작
 Serial1.begin(9600); // 통신 속도 9600bps로 블루투스 시리얼 통신 시작
 Keyboard.begin();
 Mouse.begin();

}

void loop()
{

  if (Serial1.available()){
    
    String inString = Serial1.readStringUntil('\n');
    String inString1 = inString.substring(0, 3);
    if(inString1.equals("JJJ")){
      String inString2 = inString.substring(3,7);
      String inString3 = inString.substring(7,11);
      int XV = inString2.toInt()/50;
      int YV = inString3.toInt()/50;
      Serial.println(XV);
      Serial.println(YV);
      Serial.println("VVVV");
      Mouse.move(XV, YV);
    }
    else if(inString1.equals("CCL")){
      Mouse.click();
    }
    else if(inString1.equals("CCR")){
      Mouse.click(MOUSE_RIGHT);
    }
    else if(inString1.equals("CLL")){
      Mouse.press(MOUSE_LEFT);
    }
    else if(inString1.equals("CLR")){
      Mouse.press(MOUSE_RIGHT);
    }
    else if(inString1.equals("BBS")){
      Keyboard.press(KEY_BACKSPACE);
      Keyboard.release(KEY_BACKSPACE);
    }
    else if(inString1.equals("KRE")){
      Keyboard.press(KEY_RIGHT_CTRL);
      Keyboard.press(KEY_RIGHT_ALT);
      Keyboard.release(KEY_RIGHT_CTRL);
      Keyboard.release(KEY_RIGHT_ALT);
    }
   
    else if(inString1.equals("WUP")){
      Serial.println("휠업");
      Mouse.move(0, 0, 1);

    }
    else if(inString1.equals("WDO")){
      Serial.println("휠다운");
      Mouse.move(0, 0, -1);
    }
    else if(inString1.equals("ETT")){
      Keyboard.press(KEY_RETURN);
      Keyboard.release(KEY_RETURN);
    }
    else{
      Serial.println(inString);
      Keyboard.print(inString);
      for(int i = 0; i < inString.length(); i++){
         String w = inString.substring(i,i+1);
         Serial.println(w);
      }
    }
    
  }

  // Serial 핀에 입력이 들어오면, 바이트단위로 읽어서 블루투스로 출력
 if (Serial.available()){
   Serial1.write(Serial.read());
  
 }
}

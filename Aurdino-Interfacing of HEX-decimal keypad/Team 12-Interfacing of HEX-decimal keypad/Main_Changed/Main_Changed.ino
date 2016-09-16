#include<LiquidCrystal.h>
LiquidCrystal lcd(13,12,11,10,9,8);
const int r1=7;
const int r2=6;
const int r3=5;
const int r4=4;
const int c1=3;
const int c2=2;
const int c3=1;
void alphkeypad();
void setup()
{
lcd.begin(16 , 2);
lcd.clear();
pinMode(r1,OUTPUT);
pinMode(r2,OUTPUT);
pinMode(r3,OUTPUT);
pinMode(r4,OUTPUT);
pinMode(c1,INPUT);
pinMode(c2,INPUT);
pinMode(c3,INPUT);
}
void loop()
{
  int i=0;
lcd.setCursor(0, 1);
lcd.print('A');
delay(5000);
alphkeypad();
}
void alphkeypad(){
//lcd.setCursor(0, 1);
char a='a';
while(a!='c'){
digitalWrite(c1,HIGH);  digitalWrite(c2,HIGH);digitalWrite(c3,HIGH);
    digitalWrite(r1,LOW);digitalWrite(r2,HIGH);
    digitalWrite(r3,HIGH);digitalWrite(r4,HIGH);
    if(digitalRead(c1)==LOW){
    //lcd.clear();
    lcd.print('1');delay(500);lcd.clear();
      if(digitalRead(c1)==LOW){
     lcd.clear(); lcd.print('a');delay(500);
        if(digitalRead(c1)==LOW){
       lcd.clear(); lcd.print('b');delay(500);
          if(digitalRead(c1)==LOW){
        lcd.clear();  lcd.print('c');delay(500);}}}
    a='c';    
  
}
  
  
    digitalWrite(r1,LOW);digitalWrite(r2,HIGH);
    digitalWrite(r3,HIGH);digitalWrite(r4,HIGH);
    if(digitalRead(c2)==LOW){    
//lcd.clear();
lcd.print('2');delay(500);
      if(digitalRead(c2)==LOW){
      lcd.clear();lcd.print('d');delay(500);
        if(digitalRead(c2)==LOW){
        lcd.clear();lcd.print('e');delay(500);
          if(digitalRead(c2)==LOW){
          lcd.clear();lcd.print('f');delay(500);}}}
    a='c';
            
}
  
   
    digitalWrite(r1,LOW);digitalWrite(r2,HIGH);
    digitalWrite(r3,HIGH);digitalWrite(r4,HIGH);
    if(digitalRead(c3)==LOW){
    //lcd.clear();
lcd.print('3');delay(500);
      if(digitalRead(c3)==LOW){
      lcd.clear();lcd.print('g');delay(500);
        if(digitalRead(c3)==LOW){
        lcd.clear();lcd.print('g');delay(500);
          if(digitalRead(c3)==LOW){
          lcd.clear();lcd.print('i');delay(500);}}}
           a='c';  
  }
  
   
    digitalWrite(r1,HIGH);digitalWrite(r2,LOW);
    digitalWrite(r3,HIGH);digitalWrite(r4,HIGH);
    if(digitalRead(c1)==LOW){
    //lcd.clear();
lcd.print('4');delay(500);
      if(digitalRead(c1)==LOW){
      lcd.clear();lcd.print('j');delay(500);
        if(digitalRead(c1)==LOW){
        lcd.clear();lcd.print('k');delay(500);
          if(digitalRead(c1)==LOW){
          lcd.clear();lcd.print('l');delay(500);}}}
          a='c';  
  }
  
     
    digitalWrite(r1,HIGH);digitalWrite(r2,LOW);
    digitalWrite(r3,HIGH);digitalWrite(r4,HIGH);
    if(digitalRead(c2)==LOW){
    //lcd.clear();
lcd.print('5');delay(500);
      if(digitalRead(c2)==LOW){
      lcd.clear();lcd.print('m');delay(500);
        if(digitalRead(c2)==LOW){
        lcd.clear();lcd.print('n');delay(500);
          if(digitalRead(c2)==LOW){
          lcd.clear();lcd.print('o');delay(500);}}}
          a='c';  
  }
  
  
     
    digitalWrite(r1,HIGH);digitalWrite(r2,LOW);
    digitalWrite(r3,HIGH);digitalWrite(r4,HIGH);
    if(digitalRead(c3)==LOW){
   // lcd.clear();
lcd.print('6');delay(500);
      if(digitalRead(c3)==LOW){
      lcd.clear();lcd.print('p');delay(500);
        if(digitalRead(c3)==LOW){
        lcd.clear();lcd.print('q');delay(500);
          if(digitalRead(c3)==LOW){
          lcd.clear();lcd.print('r');delay(500);}}}
          a='c';
    }  
      
    digitalWrite(r1,HIGH);digitalWrite(r2,HIGH);
    digitalWrite(r3,LOW);digitalWrite(r4,HIGH);
    if(digitalRead(c1)==LOW){
   // lcd.clear();
lcd.print('7');delay(500);
      if(digitalRead(c1)==LOW){
      lcd.clear();lcd.print('s');delay(500);
        if(digitalRead(c1)==LOW){
        lcd.clear();lcd.print('t');delay(500);
          if(digitalRead(c1)==LOW){
          lcd.clear();lcd.print('u');delay(500);}}}
          a='c'   ;
    }
  
     
    digitalWrite(r1,HIGH);digitalWrite(r2,HIGH);
    digitalWrite(r3,LOW);digitalWrite(r4,HIGH);
    if(digitalRead(c2)==LOW){
    //lcd.clear();
lcd.print('8');delay(500);
      if(digitalRead(c2)==LOW){
      lcd.clear();lcd.print('v');delay(500);
        if(digitalRead(c2)==LOW){
        lcd.clear();lcd.print('w');delay(500);
          if(digitalRead(c2)==LOW){
          lcd.clear();lcd.print('x');delay(500);}}}
          a='c';
    }
  
    digitalWrite(r1,HIGH);digitalWrite(r2,HIGH);
    digitalWrite(r3,LOW);digitalWrite(r4,HIGH);
    if(digitalRead(c3)==LOW){
    //lcd.clear();
lcd.print('9');delay(500);
      if(digitalRead(c3)==LOW){
      lcd.clear();lcd.print('y');delay(500);
        if(digitalRead(c3)==LOW){
        lcd.clear();lcd.print('z');delay(500);
          }}
          a='c';
    } 
  
     digitalWrite(r1,HIGH);digitalWrite(r2,HIGH);
    digitalWrite(r3,HIGH);digitalWrite(r4,LOW);
    if(digitalRead(c1)==LOW){
    //lcd.clear();
lcd.print('*');delay(500);
      if(digitalRead(c1)==LOW){
      lcd.clear();lcd.print('(');delay(500);
        if(digitalRead(c1)==LOW){
        lcd.clear();lcd.print(')');delay(500);
          if(digitalRead(c1)==LOW){
          lcd.clear();lcd.print('v');delay(500);}}}
          a='c';
    }
  
    digitalWrite(r1,HIGH);digitalWrite(r2,HIGH);
    digitalWrite(r3,HIGH);digitalWrite(r4,LOW);
    if(digitalRead(c2)==LOW){
   // lcd.clear();
lcd.print('0');delay(500);
      if(digitalRead(c2)==LOW){
      lcd.clear();lcd.print('&');delay(500);
        if(digitalRead(c2)==LOW){
        lcd.clear();lcd.print('|');delay(500);
          if(digitalRead(c2)==LOW){
          lcd.clear();lcd.print('!');delay(500);}}}
          a='c';
    }
      digitalWrite(r1,HIGH);digitalWrite(r2,HIGH);
    digitalWrite(r3,HIGH);digitalWrite(r4,LOW);
    if(digitalRead(c3)==LOW){
   // lcd.clear();
lcd.print('#');delay(500);
      if(digitalRead(c3)==LOW){
      lcd.clear();lcd.print('%');delay(500);
        if(digitalRead(c3)==LOW){
        lcd.clear();lcd.print('^');delay(500);
          if(digitalRead(c3)==LOW){
          lcd.clear();lcd.print('&');delay(500);}}}
          a='c';
    }
 
  }//WHILE ENDING
}//KEYPAD  ENDING


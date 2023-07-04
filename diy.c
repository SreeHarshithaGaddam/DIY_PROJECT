#include <Wire.h>
#include "paj7620.h"

#define GES_REACTION_TIME    500     
#define GES_ENTRY_TIME      500        
#define GES_QUIT_TIME     300
char s[4];
char pswd[4];
int p1=0;// pointer
int p2=0;
const int pin1=2;
const int pin2=3;
const int pin3=4;
const int pwm = 6;  
const int in_1 = 7 ;
const int in_2 = 8 ;

/*const int pwm1= 9;
const int in_11= 10;
const int in_21= 11; 
int x;
int y;*/
void setup()
{
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
  pinMode(pwm,OUTPUT) ;   
  pinMode(in_1,OUTPUT) ; 
  pinMode(in_2,OUTPUT) ;
  //pinMode(pwm1,OUTPUT);
  //pinMode(in_11,OUTPUT);
  //pinMode(in_21,OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);
  paj7620Init();
  //Serial.begin(9600);
}
char setpwd()
{
  digitalWrite(pin2,HIGH);
  //char sorry="Try Again";
  if(p1<4)
  {
    uint8_t data=0,error;
    error=paj7620ReadReg(0x43,1,&data);
    if(!error)
    {
      switch(data)
      {
        case GES_RIGHT_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        printing();digitalWrite(LED_BUILTIN,LOW);digitalWrite(pin1,LOW);
        //Serial.println("Right");
        pswd[p1]='R';p1++;
        break;
      case GES_LEFT_FLAG: 
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        printing();digitalWrite(LED_BUILTIN,LOW);digitalWrite(pin1,LOW);
        //Serial.println("Left");
        pswd[p1]='L';p1++;
        break;
      case GES_UP_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        printing();digitalWrite(LED_BUILTIN,LOW);digitalWrite(pin1,LOW);
        //Serial.println("Up");
        pswd[p1]='U';p1++;
        break;
      case GES_DOWN_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        printing();digitalWrite(LED_BUILTIN,LOW);digitalWrite(pin1,LOW);
        //Serial.println("Down");
        pswd[p1]='D';p1++;
        break;
      default:break;
      }
    }
  }
  else
  {
    //Serial.println("Setting pwd");
  }
}
void printing(){
  //Serial.print("Gesture Sensor: ");
  digitalWrite(LED_BUILTIN,HIGH);
  digitalWrite(pin1,HIGH);
  delay(1000);
}

int equal()
{
  int i;
  for(i=0;i<4;i++)
  if(pswd[i]!=s[i])
  return(0);
  return (1);
}

/*void loop() 
{
int result;
  if(p1<4)
  {
    setpwd();
    result=equal();
   if(result==1)
    {
      //Serial.println("Unlocked");
   digitalWrite(5, HIGH);//pin of green led
   digitalWrite(6, HIGH);// pin of motor
    }
   else 
    {
       //Serial.println("Try again");
  digitalWrite(3, LOW);//pin of red led
  digitalWrite(6, LOW);//pin of motor
    }
    ////Serial.println("Setting pwd");
    ////Serial.println(pswd);
  }
}*/
void delayer(unsigned long t,long s)
{
  unsigned long TimeNow=millis();
  if(TimeNow-t>=s)
  return;
  delayer(t,s);
}
void runmotor()
{
  digitalWrite(pin1,HIGH);//LED turned n
  //For C-Clock wise motion , in_1=LOW , in_2 =HIGH.
int i,j;
digitalWrite(in_1,LOW);
digitalWrite(in_2,HIGH);
/*for(i=50;i<125;i++) 
{
 analogWrite(pwm,i);
 delay(100);
}
analogWrite(pwm,125);
delay(4000);
for(i=124;i>0;i--) 
{
 analogWrite(pwm,i);
 delay(100);
}*/
unsigned long t=millis();
analogWrite(pwm,200);
for(i=1;i<=4;i++)
delay(1000);
//For brake
digitalWrite(in_1,HIGH) ;
digitalWrite(in_2,HIGH) ;
for(i=1;i<=5;i++)
delay(1000);

digitalWrite(in_1,HIGH);
digitalWrite(in_2,LOW);
analogWrite(pwm,200);
for(i=1;i<=4;i++)
delay(1000);
digitalWrite(in_1,HIGH) ;
digitalWrite(in_2,HIGH) ;
/*//For Clock-wise motion - In_11 = HIGH , In_12 = LOW.
digitalWrite(in_11,HIGH) ;
digitalWrite(in_21,LOW) ;
analogWrite(pwm1,225);
delay(8000) ;
/*for(j=0;j<125;j++)
{
analogWrite(pwm1,j);
delay(100);
}
//For brake
digitalWrite(in_11,HIGH) ;
digitalWrite(in_21,HIGH) ;
delay(1000) ;*/
digitalWrite(pin1,LOW);
}
void loop() {
  if(p1<4){
    setpwd();
    ////Serial.println(pswd);
  }
  else{
  digitalWrite(pin2,LOW);
  digitalWrite(pin3,LOW);
  uint8_t data = 0, data1 = 0, error;
  error = paj7620ReadReg(0x43, 1, &data);       // Read Bank_0_Reg_0x43/0x44 for gesture result.
  if (!error) 
  {
    //data,data1,dat2,dat3
    switch (data) // When different gestures be detected, the variable 'data' will be set to different values by paj7620ReadReg(0x43, 1, &data).
    {
      case GES_RIGHT_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        printing();digitalWrite(LED_BUILTIN,LOW);digitalWrite(pin1,LOW);
        //Serial.println("Right");//Three LEDs- Green, Red, Yellow
        s[p2]='R';p2++;
        ////Serial.println(s);
        break;// 4 Gesture Code. ULLU.
        // 4 variables of uint type.
      case GES_LEFT_FLAG: 
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        printing();digitalWrite(LED_BUILTIN,LOW);digitalWrite(pin1,LOW);
        //Serial.println("Left");
        s[p2]='L';p2++;////Serial.println(s);
        break;
      case GES_UP_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        printing();digitalWrite(LED_BUILTIN,LOW);digitalWrite(pin1,LOW);
        //Serial.println("Up");
        s[p2]='U';p2++;////Serial.println(s);
        break;
      case GES_DOWN_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        printing();digitalWrite(LED_BUILTIN,LOW);digitalWrite(pin1,LOW);
        //Serial.println("Down");
        s[p2]='D';p2++;////Serial.println(s);
        break;
      case GES_CLOCKWISE_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data==GES_RIGHT_FLAG)
        {
          printing();//Serial.println("RIGHT");
        }
        else if(data==GES_LEFT_FLAG)
        {
          printing();//Serial.println("LEFT");
        }
        else{
        printing();
        //Serial.println("Clockwise");
        //p1=0;setpwd();
        }
        break;
      case GES_COUNT_CLOCKWISE_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data==GES_RIGHT_FLAG)
        {
          printing();digitalWrite(LED_BUILTIN,LOW);
          //Serial.println("RIGHT");
        }
        else if(data==GES_LEFT_FLAG)
        {
          printing();digitalWrite(LED_BUILTIN,LOW);
          //Serial.println("LEFT");
        }
        else{
        printing();
        //Serial.println("anti-clockwise");}
        break;  
      default:
        paj7620ReadReg(0x44, 1, &data1);
        if (data1 == GES_WAVE_FLAG) 
        {
          printing();
          //Serial.print("wave");
        }
        break;
    }
  }
  int result; 
  if(p2==4)
  {
    result=equal();
   if(result==1)
    {
      //Serial.println("Unlocked");
      runmotor();
      p2=0;
    }
   else 
    {
       digitalWrite(pin3, HIGH);//pin of red led
       //digitalWrite(6, LOW);//pin of motor
       //Serial.println("Incorrect");
       p2=0;
       //Serial.println(s);
       ////Serial.println(pswd);
       int i;
       //for(i=0;i<4;i++)
       //Serial.print(pswd[i]);
       //Serial.println();
    }
  delay(100);
  }
  }
}
}
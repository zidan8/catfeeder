#include <RFID.h>
#include <Servo.h>
#include <WProgram.h>
#include <Wire.h
#include <DS1307.h>
#include <Time.h>
#include <SPI.h>
#include "MFRC522.h"

#define SS 10
#define RST 9

byte i;
boolean valid_card = true;
if (rfid.isCard())
{
  if(rfid.readCardSerial())
  {
    delay(200);
    date[0] = rfid.serum[0];
    date[1] = rfid.serum[1];
    date[2] = rfid.serum[2];
    date[3] = rfid.serum[3];
    date[4] = rfid.serum[4];
  }
}

Serial.print{"Card Detected: "};
for(int i=0; i<=4; i++)
{
  Serial.print(rfid.serNum[1],HEX);
  Serial.print(" ");
  delay(100);

  if (data[i] !=valid[i]) valid_card = false;
  {
    Serial.print(" ");
  }
}

byte nuidPICC[4];
MFRC522 rfid(SS, RST);
MFRC522::MIFARE_Key key;

RFID rfid(10,9);
byte valid[5] = {0xF4,0xB8,0x46,0xA,0x0};
byte serNum[5];
byte data[5];

Servo myservo;
int pos = 0;
const int ServoPin = 8;

void time()
{
  int tmp=1,mins=0,hors=0,secs=0;
    while(tmp==1)
    {
     off=0;
     if(digitalRead(cge)==0)
     {
      Hor++;
      if(Hor==24)
      {
       Hor=0;
      }
     }
     if(digitalRead(set)==0)
     {
       hor=Hor;
       EEPROM.write(add++,hor);
       tmp=2;
       while(digitalRead(set)==0);
      }
    }
    while(tmp==2)
    {
      if(digitalRead(cge)==0)
      {
        Min++;
        if(Min==60)
        {Min=0;}
      }
      if(digitalRead(set)==0)
      {
        mIn=Min;
        EEPROM.write(add++, mIn);
        tmp=0;
        while(digitalRead(set)==0);
      }
    }
    off=1;
    delay(10);
}

void TimeCheck()
{
  int tem[17];
  for(int i=11;i<17;i++)
  {
    tem[i]=EEPROM.read(i);
  }
  if(Hor == tem[7]&& MIN == tem[0] && off== 1)
  {
    add=7;
  }
  else if(Hor == tem[13]&& MIN == tem[0] && off== 1)
  {
    add=13;
  }
  else if(Hor == tem[18]&& MIN == tem[0] && off== 1)
  {
    add=18;
  }
}

void setup() 
{
  Wire.begin();
  RTC.begin();
  Serial.begin(9600);
  myservo.attach(8);
  setTime(7,00,0,4,8,17);
  SPI.begin();
  rfid.PCD_init();
  delay(1000);
  if(!RTC.isrunning())
  {
    RTC.adjust(DateTime(__DATE__,__TIME__));
  }
}
void loop()
{
  if (valid_card)
  {
    DateTime now = RTC.now()
    if(digitalRead(mod) == 0)
    {
      current();
      time();
      myservo.write(-60);
      delay(5000);
      myservo.write(pos);
      delay(1000);
    }
  }
  else
  {
    myservo.write(60);
    delay(50);
    myservo.write(pos);
    delay(1000);
  }
}

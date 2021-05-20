#include <Wire.h>
#define sensor A0
#define lcd_address 0x3e

float readvalue,temp,vol; 

void writeCommand(uint8_t command) {
  Wire.beginTransmission(lcd_address);
  Wire.write(0x0);
  Wire.write(command);
  Wire.endTransmission();
}

void writeData(uint8_t data) {
  Wire.beginTransmission(lcd_address);
  Wire.write(0x40);
  Wire.write(data);
  Wire.endTransmission();
}

void initLcd() {
  delay(40);
  writeCommand(0x38); 
  delay(1);
  writeCommand(0x39); 
  delay(1);
  writeCommand(0x14); 
  delay(1);
  writeCommand(0x73); 
  delay(1);
  writeCommand(0x5e); 
  delay(1);
  writeCommand(0x6c); 
  delay(1);
  writeCommand(0x38); 
  delay(1);
  writeCommand(0x0c); 
  delay(1);
  writeCommand(0x01); 
  delay(1);
}

void setcursor(int x, int y) {
  byte Cursor=0x80;
  Cursor|=x;
  if(y>0&&y<=1)
  {
    Cursor|=0x40;
  }
  writeCommand(Cursor);
}

void print_c(char *s)
{
  int len = strlen(s);
  
  for (int i = 0;i < len; i++) {
    writeData((uint8_t)s[i]);
  }
}
void setup() {
  Serial.begin(9600);
  Wire.begin();
  initLcd();

  setcursor(5, 0);
  print_c("hello");
  setcursor(1, 1);
  print_c("temp = ");
  setcursor(13, 1);
  print_c("*C");
}

void loop() {
  readvalue=analogRead(sensor);
  vol=(readvalue*3.3)/1023;
  temp = (vol*1000-600)/10;
  setcursor(8 , 1);
  char cstr[50];
  dtostrf(temp,3,2,cstr);
  print_c(cstr);
  delay(500);
}

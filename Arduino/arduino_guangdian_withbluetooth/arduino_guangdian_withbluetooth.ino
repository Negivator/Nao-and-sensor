#include <SoftwareSerial.h>
SoftwareSerial port_to_controller(3, 2); // 实例化软串口 （RX, TX） rx=3 tx=2
int guangdianduiguan_temp = 0;
int soilhemidity_temp = 0;
int sendnum = 0;
void setup() {
// put your setup code here, to run once:
Serial.begin(9600);//硬件串口设定波特率38400
port_to_controller.begin(9600);//软串口波特率设定9600
pinMode(A1, INPUT); //设置为输入状态
pinMode(4, INPUT); //设置为输入状态
}

void loop() {
  // put your main code here, to run repeatedly:
guangdianduiguan_temp = digitalRead(A1);
soilhemidity_temp = digitalRead(4);
if(guangdianduiguan_temp ==0)
{if(soilhemidity_temp==0)
 {sendnum = 0;}
 else
 {sendnum = 1;}
}
if(guangdianduiguan_temp == 1)
{if(soilhemidity_temp==0)
 {sendnum = 2;}
 else
 {sendnum = 3;}
}
port_to_controller.print(sendnum);
//Serial.println("guang:");
//Serial.println(guangdianduiguan_temp);
//Serial.println("sedi:");
//Serial.println(soilhemidity_temp);
delay(5);
}

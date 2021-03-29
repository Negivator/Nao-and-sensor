#include <SoftwareSerial.h>
SoftwareSerial port_to_sensor(3, 2); // 实例化软串口 （RX, TX） rx=3 tx=2
SoftwareSerial port_to_water(11, 12); // 实例化软串口 （RX, TX） rx=11 tx=12
int led1 = 4;  //led灯1
int led2 = 5;  //led灯2
int led3 = 6;  //led灯3
int jidianqi1 = 9;  //继电器1控制插座
int jidianqi2 = 10;  //继电器2控制插座 
int motor1= 7;    //电机正转控制继电器
int motor2 =8;    //电机反转控制继电器

String data_from_sensor = "";     //从sensor传来的数据
int rev_mark = 0;
int correct_mark = 0;

String  data_from_water = "";
int  rev_water_mark = 0;
char  waternum = 'n';

char yuyin_rev_mark = 0; 
int nao_command = 0;
int listendata = 0;
int count = 0;
int counting = 0;
int val = 0;

void setup() {

Serial.begin(9600);//硬件串口设定波特率38400
port_to_sensor.begin(9600);//软串口波特率设定9600
port_to_water.begin(9600);//软串口波特率设定9600

pinMode(led1, OUTPUT); //设置LED2为输出状态
digitalWrite(led1, LOW);
pinMode(led2, OUTPUT); //设置LED1为输出状态
digitalWrite(led2, LOW);
pinMode(led3, OUTPUT); //设置LED2为输出状态
digitalWrite(led3, LOW);
pinMode(jidianqi1, OUTPUT); //设置插座1为输出状态
digitalWrite(jidianqi1, LOW);
pinMode(jidianqi2, OUTPUT); //设置插座2为输出状态
digitalWrite(jidianqi2, LOW);
pinMode(motor1, OUTPUT); //设置电机1为输出状态
digitalWrite(motor1, LOW);
pinMode(motor2, OUTPUT); //设置电机2为输出状态
digitalWrite(motor2, LOW);

delay(5000);
port_to_sensor.print("start");
}

void loop() 
{
//while (Serial.available() > 0)//首先检查是否接收到来自服务器的数据  
//  {
//    listendata = Serial.read();
//    delay(2);
//    yuyin_rev_mark = 1;
//  }
//  
//  if(yuyin_rev_mark == 1) //这部分其实可以用一个字符串转换语句 将收到的数字改成command
//{
//    nao_command = listendata;
//    listendata = 0;
//    yuyin_rev_mark = 1;
//}
val = Serial.read();//读取串口接收到的值
  if (-1 != val)//如果串口接收到数据了，那val肯定不等于-1（没接收到数据时是等于-1的，arduino串口基础，不多说。）
  {
   nao_command = val;
  }

port_to_sensor.listen();
delay(15);
while (port_to_sensor.available() > 0)  
  {
    data_from_sensor += char(port_to_sensor.read());
    delay(2);
    rev_mark = 1;
  }
  
if(rev_mark == 1) 

{
     if(data_from_sensor == "d")//1有干扰 试试21
     {
     digitalWrite(led1, HIGH);
     correct_mark = 1;
     }
     if(data_from_sensor == "2")
     {
     digitalWrite(led1, LOW);
     correct_mark = 1;
     }
     if(data_from_sensor == "3")
     {
     digitalWrite(led2, HIGH);
     correct_mark = 1;
     }
     if(data_from_sensor == "4")
     {
     digitalWrite(led2, LOW);
     correct_mark = 1;
     }
     if(data_from_sensor == "5")
     {
     digitalWrite(led3, HIGH);
     correct_mark = 1;
     }
     if(data_from_sensor == "6")
     {
     digitalWrite(led3, LOW);
     correct_mark = 1;
     }
      if(data_from_sensor == "7")
     {
     digitalWrite(motor2, LOW);
     digitalWrite(motor1, HIGH);
     correct_mark = 1;
     }
     if(data_from_sensor == "8")
     {
     digitalWrite(motor1, LOW);
     digitalWrite(motor2, HIGH);
     correct_mark = 1;
     }
     if(data_from_sensor == "9")
     {
     digitalWrite(jidianqi1, HIGH);
     correct_mark = 1;
     }
     if(data_from_sensor == "a")
     {
     digitalWrite(jidianqi1, LOW);
     correct_mark = 1;
     }
      if(data_from_sensor == "b")
     {
     digitalWrite(jidianqi2, HIGH);
     correct_mark = 1;
     }
     if(data_from_sensor == "c")
     {
     digitalWrite(jidianqi2, LOW);
     correct_mark = 1;
     }
     if((data_from_sensor[0] == 'z')||(data_from_sensor[1] == 'z')||(data_from_sensor[2] == 'z'))
     {
     nao_command = 0; 
     correct_mark = 1;
     }
     if(correct_mark == 1)
     {
      correct_mark =0;
      }
     data_from_sensor = "";
     rev_mark = 0;
  }

port_to_water.listen();
delay(5);
while (port_to_water.available() > 0)  
  {
    data_from_water += char(port_to_water.read());
    rev_water_mark = 1;
  }
if(rev_water_mark == 1)
{
  if(data_from_water[0] == '0')
  {waternum = 'a';}
  if(data_from_water[0] == '1')
  {waternum = 'b';}
  if(data_from_water[0] == '2')
  {waternum = 'c';}
  if(data_from_water[0] == '3')
  {waternum = 'd';}
  count++;

  data_from_water = "";
  rev_water_mark = 0;
}

counting++;
if(counting > 1)
 {
counting = 0;
port_to_sensor.print(waternum);
port_to_sensor.print(nao_command);

  }
}

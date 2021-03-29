#include <dht.h> 
#include <SoftwareSerial.h>
#include <Wire.h>
#include <SPI.h>
#include <PS2X_lib.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);//每块lcd I2C地址都要修改
SoftwareSerial port_to_controller(3, 2); // 实例化软串口 （RX, TX） rx=3 tx=2
SoftwareSerial port_to_door(6, 5); // 实例化软串口 （RX, TX） rx=8 tx=7

dht DHT; 
#define DHT11_PIN A0 //DHT11 接 Arduino Uno A0
#define MQ135_PIN A1 //MQ-135  接Arduino Uno A1
#define FIRE_CK015_PIN A2 //火焰传感器  接Arduino Uno A2
#define LIGHT_PIN A3 //光敏电阻  接Arduino Uno A3
int led = 13;//LED指示灯接Arduino Uno D13
int bodysensor_pin = 4;//人体热释电传感器接Arduino Uno D4
/*   PS2:       ARDUINO
   PS2_DAT<--->D7
   PS2_CMD<--->D8
   PS2_SEL<--->D9
   PS2_CLK<--->D10*/
#define PS2_DAT        9     
#define PS2_CMD        10 
#define PS2_SEL        11
#define PS2_CLK        12 

#define pressures   false
#define rumble      false

PS2X ps2x; // create PS2 Controller Class

int sensorid = 999;//用于发送给服务器说明程序来源于sensor 就是sensor的id

//以下变量属于ps2状态
int error = 0; //
byte type = 0;
byte vibrate = 0;

int count = 0; //用于
int count_door = 0;//用于人脸识别设施电平信号有效时长计数（是指触发一次信号后flag不到一定数值后不再计数）
int flag = 1; //用于ps2的有效时长计数
int flag_door = 0;//
void (* resetFunc) (void) = 0;

int yanwu_temp = 0; //临时变量，存储A1烟雾报警器读取的数据
int fire_temp = 0;//存放火焰传感器数值的变量 
int light_temp = 0; //存放光敏电阻数值的变量
int soil_humidity = 0;
int nao_command = 0;
int command_sending = 0;
boolean clothes_status = 0;
boolean led1_status = 0;
boolean led2_status = 0;
boolean led3_status = 0;
boolean motor_status = 0;
boolean plug1_status = 0;
boolean plug2_status = 0;

int mark_get_ctl = 0;//接收到controller信息的标志位
int mark_get_door = 0;//接收到door信息的标志位
int mark_get_listen = 0;//接收到语音模块信息的标志位
int server_rev_mark = 0;//接收server信息的标志位
int control_command = 0;//真正发送给door或者contoller的数据
unsigned int count_send = 0;//循环在到达一定数值后才向服务器发送数据

String serverdata = "";//从server接收的信息
String data_from_ctl = "";//从controller接收的信息
String data_from_door = "";//从door接收的信息
int listendata = 0;

char inchar = 0;
String data_ctl_char = "";
String intchars = "";
int flaging = 0;
int countshoubing = 0;
int receive_listen_flag = 0;

void setup(){ 
  Serial.begin(9600);//硬件串口设定波特率38400
  port_to_controller.begin(9600);//软串口波特率设定9600
  port_to_door.begin(9600);//软串口波特率设定9600
  pinMode(MQ135_PIN, INPUT); //设置污染报警器为输入状态
  pinMode(FIRE_CK015_PIN, INPUT);//设置火焰传感器输入状态
  pinMode(LIGHT_PIN,INPUT);//设置光敏电阻输入状态
  pinMode(bodysensor_pin,INPUT); //设置人体红外接口为输入状态
  pinMode(led, OUTPUT); //设置LED为输出状态
  digitalWrite(led, LOW);

  lcd.init();//液晶1602初始化 i2c通讯
  lcd.backlight();
  lcd.print(" Nice to see you!");
  
    //下面一行代码对于手柄遥控必不可少
error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble); 
delay(500);

} 
void loop(){                                           //主循环
   
   while (Serial.available() > 0)//首先检查是否接收到来自服务器的数据  
  {
    serverdata += char(Serial.read());
//    delay(2);
    server_rev_mark = 1;
  }
  
  if(server_rev_mark == 1) //这部分其实可以用一个字符串转换语句 将收到的数字改成command
{
     if(serverdata== "21")
     control_command = 21;
     if(serverdata== "61")
     control_command = 21;
     if(serverdata == "2")
     control_command = 2;
     if(serverdata == "62")
     control_command = 2;
     if(serverdata == "3")
     control_command = 3;
     if(serverdata == "63")
     control_command = 3;
     if(serverdata == "4")
     control_command = 4;
     if(serverdata == "64")
     control_command = 4;
     if(serverdata == "5")
     control_command = 5;
     if(serverdata == "65")
     control_command = 5;
     if(serverdata == "6")
     control_command = 6;
     if(serverdata == "67")
     control_command = 6;
     if(serverdata == "68")
     control_command = 7;
     if(serverdata == "7")
     control_command = 7;
     if(serverdata == "69")
     control_command = 8;
     if(serverdata == "8")
     control_command = 8;
     if(serverdata == "91")
     control_command = 9;
     if(serverdata == "9")
     control_command = 9;
     if(serverdata == "10")
     control_command = 10;
     if(serverdata == "93")
     control_command = 10;
     if(serverdata == "11")
     control_command = 11;
     if(serverdata == "94")
     control_command = 11;
     if(serverdata == "12")
     control_command = 12;
     if(serverdata == "95")
     control_command = 12;
    
     if(serverdata == "51")   //这部分是发送给door的数据
     control_command = 51;
     if(serverdata == "59")   
     control_command = 51;
     if(serverdata == "52")
     control_command = 52;
     if(serverdata == "53")
     control_command = 53;
     if(serverdata == "54")
     control_command = 54;
     if(serverdata == "55")
     control_command = 55;
     if(serverdata == "56")
     control_command = 56;
     
     if(serverdata == "99")
     command_sending = 0;
     serverdata = "";
     server_rev_mark = 0;
     lcd.setCursor(15, 1);
     lcd.print("y");
 }

countshoubing++;
//手柄控制门锁
  if(error == 1)                                 //error type 现阶段没用到
  { //skip loop if no controller found
  }  
  if(type == 2)
  { //Guitar Hero Controller
  }  
  else
  {                       //DualShock Controller
    if(countshoubing > 2)//200
    {
    countshoubing = 0;
    ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed
    vibrate = ps2x.Analog(PSAB_CROSS);  //this will set the large motor vibrate speed based on how hard you press the blue (X) button
    if (ps2x.NewButtonState()) 
    {//will be TRUE if any button changes state (on to off, or off to on)
      if(ps2x.Button(PSB_L3) && (flag == 1))
        {
        control_command = 51;
        flag = 0;}
      if(ps2x.Button(PSB_R3) && (flag == 1))
        {
        control_command = 54;
        flag = 0;}
      if(ps2x.Button(PSB_L2) && (flag == 1))
        {
         control_command = 21;
         led1_status = 1;
          flag = 0;
        }
      if(ps2x.Button(PSB_R2) && (flag == 1))
        {
        control_command = 2;
        led1_status = 0;
        flag = 0;
        }
      if(ps2x.Button(PSB_TRIANGLE) && (flag == 1))
        {
         //Serial.println("Triangle pressed");
         flag = 0; 
        }   
    }
    
    if(ps2x.ButtonPressed(PSB_CIRCLE) && (flag == 1))               //will be TRUE if button was JUST pressed
      {//Serial.println("Circle just pressed");
      control_command = 3;
      led2_status = 1;
      flag = 0;}
    if(ps2x.NewButtonState(PSB_CROSS) && (flag == 1))               //will be TRUE if button was JUST pressed OR released
      {//Serial.println("X just changed");   
      flag = 0;}
    if(ps2x.ButtonReleased(PSB_SQUARE) && (flag == 1))              //will be TRUE if button was JUST released
      {//Serial.println("Square just released");
      control_command = 4;
      led2_status = 0;
      flag = 0;}
      
   if (flag == 0)
    {
      count ++;
      if(count>0)
       {
        flag=1;
        count=0;
        }
     } 
   }            
}
//手柄程序到此为止

  port_to_controller.listen();
  delay(20);
  
  while (port_to_controller.available() > 0) 
  {
    data_from_ctl += char(port_to_controller.read());
    mark_get_ctl = 1;    
   } 
  if((mark_get_ctl == 1)||(control_command != 0))
  {
//    flaging = 1;
   if(data_from_ctl.length() ==3)  //看收到数据长度时改成大于0
   {
//    lcd.setCursor(11, 0);  //看上面一行注释
//    lcd.print(data_from_ctl);
    for(int i = 0; i< data_from_ctl.length();i++)
    {
      inchar = data_from_ctl[i];
    if(isDigit(inchar)) //是数字就执行
        {
          intchars += inchar;//数字字符串
        }
       else {
        data_ctl_char += inchar;//否则就是字符串
       }
    }
       nao_command = 0;
       nao_command = intchars.toInt();//将数字字符串转换成整数
       
       if ((nao_command == 61)||(nao_command == 62)||(nao_command == 63)||(nao_command == 64)||(nao_command == 65)||(nao_command == 67)||(nao_command == 68)||(nao_command == 69)||(nao_command == 91)||(nao_command == 93)||(nao_command == 94)||(nao_command == 95)||(nao_command == 54)||(nao_command == 77)||(nao_command == 81)||(nao_command == 88)||(nao_command == 83)||(nao_command == 84)||(nao_command == 85)||(nao_command == 86)||(nao_command == 87)||(nao_command == 89)||(nao_command == 92)||(nao_command == 20)||(nao_command == 51)||(nao_command == 22)||(nao_command == 23))
       {
        if(nao_command < 80)
     {
     if(nao_command == 61)
     {control_command = 21;}
     if(nao_command == 62)
     {control_command = 2;}
     if(nao_command == 63)
     {control_command = 3;}
     if(nao_command == 64)
     {control_command = 4;}
     if(nao_command == 65)
     {control_command = 5;}
     if(nao_command == 67)
     {control_command = 6;}
     if(nao_command == 68)
     {control_command = 7;}
     if(nao_command == 69)
     {control_command = 8;}
     if(nao_command == 91)
     {control_command = 9;}
     if(nao_command == 93)
     {control_command = 10;}
     if(nao_command == 94)
     {control_command = 11;}
     if(nao_command == 95)
     {control_command = 12;}
     }
        receive_listen_flag = 1;
        command_sending = nao_command;
        }
           
       if(data_ctl_char == "a")         //检验来自土壤湿度的数据
       {soil_humidity = 0;
       clothes_status = 0;}
       if(data_ctl_char == "b")
       {soil_humidity = 1;
       clothes_status = 0;}
       if(data_ctl_char == "c")         //检验来自土壤湿度的数据
       {soil_humidity = 0;
       clothes_status = 1;}
       if(data_ctl_char == "d")
       {soil_humidity = 1;
       clothes_status = 1;}
   }   
     
       intchars = "";
       data_ctl_char = "";  
             
  if(control_command>0)
  {
    if (control_command == 1)
    {port_to_controller.print("1");
     delay(60);
     port_to_controller.print("1");
    }
    if (control_command == 2)
    {port_to_controller.print("2");
     delay(60);
     port_to_controller.print("2");
    led1_status = 0;}
    if (control_command == 3)
    {port_to_controller.print("3");
    led2_status = 1;}
    if (control_command == 4)
    {port_to_controller.print("4");
    led2_status = 0;}
    if (control_command == 5)
    {port_to_controller.print("5");
    led3_status = 1;}
    if (control_command == 6)
    {port_to_controller.print("6");
    led3_status = 0;}
    if (control_command == 7)
    {port_to_controller.print("7");
    motor_status = 1;}
    if (control_command == 8)
    {port_to_controller.print("8");
    motor_status = 0;}
    if (control_command == 9)
    {port_to_controller.print("9");
    plug1_status = 1;}
    if (control_command == 10)
    {port_to_controller.print("a");
    plug1_status = 0;}
    if (control_command == 11)
    {port_to_controller.print("b");
    plug2_status = 1;}
    if (control_command == 12)
    {port_to_controller.print("c");
    plug2_status = 0;}
    if (control_command == 21)
    {port_to_controller.print("d");
    led1_status = 1;}
  }  
  mark_get_ctl = 0;
  data_from_ctl = "";
  }

  port_to_door.listen();
  while (port_to_door.available() > 0) 
  {
    data_from_door += char(port_to_door.read());
    delay(2);
    mark_get_door = 1;    
   } 
   
  if((mark_get_door == 1)||(control_command != 0))
  {
   
  if(control_command > 0)
  {
    if (control_command == 51)
    {port_to_door.print("1");}
    if (control_command == 52)
    {port_to_door.print("2");}
    if (control_command == 53)
    {port_to_door.print("3");}
    if (control_command == 54)
    {port_to_door.print("4");}
    if (control_command == 55)
    {port_to_door.print("5");}
    if (control_command == 56)
    {port_to_door.print("6");}
  }
  mark_get_door = 0;
  data_from_door="";
  }  
  if (receive_listen_flag == 1)
  {
    receive_listen_flag = 0;
    port_to_controller.print("z");
    delay(15);
    port_to_controller.print("z");
    delay(15);
    port_to_controller.print("z");
   }
    
  control_command = 0;
  count_send++;
  if((count_send > 90)&&(control_command == 0))  //10000
  {  
    count_send = 0;
    digitalWrite(led, HIGH);
    int chk = DHT.read11(DHT11_PIN); //read11函数,必须有
    int bodyval = digitalRead(bodysensor_pin); //定义参数存储人体红外传感器读到的状态
    yanwu_temp = analogRead(MQ135_PIN); //读取A0的模拟数据
    fire_temp = analogRead(FIRE_CK015_PIN);//读取火焰传感器数据
    light_temp = analogRead(LIGHT_PIN); //读取光敏电阻传感器数据    
    // DISPLAY DATA
    Serial.print("z");
    Serial.print(sensorid);
    Serial.print("y"); 
    Serial.print("a"); 
    Serial.print(DHT.humidity, 1); 
    Serial.print("b");
    Serial.print(DHT.temperature, 1); 
    Serial.print("c");
    Serial.print(yanwu_temp);  
    Serial.print("d");
    Serial.print(fire_temp);
    Serial.print("e");
    Serial.print(light_temp);
    Serial.print("f");
    Serial.print(bodyval);
    Serial.print("g");
    Serial.print(soil_humidity);
    Serial.print("h");    
    Serial.print(led1_status);
    Serial.print("i");    
    Serial.print(led2_status);
    Serial.print("j");    
    Serial.print(led3_status);
    Serial.print("k");    
    Serial.print(motor_status);
    Serial.print("l");    
    Serial.print(plug1_status);
    Serial.print("m");    
    Serial.print(plug2_status);
    Serial.print("n");    
    Serial.print(clothes_status);
    Serial.print("o");
    Serial.print(command_sending);
    Serial.print("p"); 
       
    digitalWrite(led, LOW);
//    nao_command = 0;
    
    lcd.clear();
    lcd.home();
    lcd.print("tempe:");
    lcd.setCursor(6, 0);
    lcd.print(DHT.temperature);
    lcd.setCursor(0, 1);
    lcd.print("humid:");
    lcd.setCursor(6, 1);
    lcd.print(DHT.humidity); 
    lcd.setCursor(12, 1);
    lcd.print(nao_command);
    lcd.setCursor(12, 0);
    lcd.print(command_sending);
    command_sending = 0;
  } 
}

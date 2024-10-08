#include <POP32.h>

  int Speed, SlowSpeed, ACCSpeed, BaseSpeed, LeftBaseSpeed, RightBaseSpeed, TurnSpeed, MaxSpeed, SonarSpeed, DistanceRef,InitialPlus;
  int Error, PreError, Kp, Kd, Ki, Kt,BackLeftBaseSpeed, BackRightBaseSpeed;
  int KpB,KdB,KtB,KiB;
  int RefL2, RefL1, RefC, RefR1, RefR2, RefBL1, RefBC, RefBR1, SumError;
  int L2, L1, C, R1, R2, BL1, BC, BR1;
  long Timer, Timer2, Timer3;
  int SW_OK_Status,Error99Check=0,digital_sw=0;
  int KnobBase;
  
  #define No 0
  #define Yes 1

  #define Mode0 0
  #define Mode1 1
  #define Mode2 2
  #define Mode3 3
  #define Mode4 4

  #define WheelDrive  0 //0:ขับเคลื่อน 2 ล้อ , 1:ขับเคลื่อน 4 ล้อ
  #define SwitchTime  200 //เวลาในการตรวจสอบการกดสวิชในหน่วย ms

  int Mode=Mode0;
  int RobotMode=3;    //3:Move the can Junior   (เซ็นเซอร์ หน้า 2 หลัง 2)

  int FontSensorNumber,BackSensorNumber;
  int HitStatus=0;    //0:ซ้าย 1:ขวา
  int PidStatus=1;    //0:กรณีโค้งน้อยๆ 1:กรณีโค้งเยอะๆ

void setup() {
  DistanceRef = 0;     //0:ไม่เช็คสิ่งกีดขวาง ,>0 เช็คสิ่งกีดขวาง 
  Speed =100;
  ACCSpeed =60;
  SlowSpeed = 60;
  BaseSpeed = Speed; 
  TurnSpeed = Speed;
  SonarSpeed = Speed;
  InitialPlus = 0;
  InitialSpeed();
  InitialRef();
  beep(0);
  oled.clear();                 //เคลียร์หน้าจอ
  oled.mode(0);                 //หมุนหน้าจอ 0 องศา
  oled.dim(true);               //ปรับความสว่างปกติ
  oled.textSize(1);             //กำหนดขนาดตัวอักษร
  oled.text(0,0," Ubon Tp Robotics");
  oled.text(1,0,"Move The Can Junior ");
  oled.text(2,0,"    Luekhamharn   ");
  oled.text(3,0,"     Speed = %d   ",Speed);
  oled.text(4,0,"     ACCSpeed=%d",ACCSpeed);
  oled.text(5,0,"   OK To Start   ");
  ShowRobotMode();    //แสดงโหมดที่เลือกไว้
  oled.show();                  //แสดงบนหน้าจอ
  SW_OK_Status = No;
  KnobBase=knob(); 
  while(SW_OK_Status == No)  {  // waiting "OK" button
      if(Read_sw_OK()) {
        StartTimer();
        Mode=Mode0; 
        SW_OK_Status = Yes;
        beep(1);
        while(Read_sw_OK())  {  //wait unpress OK button
        if(ReadTimer() >= 2000) {
          beep(2);
          delay(100);
          Grip();
          delay(1000);
          Put();
          Show4Analog();
          SW_OK_Status = No;
          }  
        }
       }
       if(SW_A()) 
       {
          StartTimer();
          beep(1);
          while(SW_A())  {}  //wait unpress SW A button
          if(ReadTimer() >= SwitchTime) Mode=Mode1;
          else  Mode=Mode2;
          SW_OK_Status = Yes;

       }
       if(SW_B()) 
       {
          StartTimer();
          beep(1);
          while(SW_B())  {}  //wait unpress SW A button
          if(ReadTimer() >= SwitchTime) Mode=Mode3;
          else  Mode=Mode4;
          SW_OK_Status = Yes;
       }
        //CheckKnobMode();  //เช็คดูว่ามีการปรับค่า knob เพื่อเปลี่ยนโหมดหรือไม่  
  }
  BaseSpeed = Speed;
  oled.clear();
  oled.textSize(2);
  oled.text(0,0,"  Starting   ");
  oled.text(1,0,"  Mode=%d   ",Mode);
  oled.show();
  StartTimer2();
  SelectSpeed();

  //ForwardSpeedTime(BaseSpeed,1500);
  //BackwardSpeedTime(BaseSpeed,1500); 
  //TurnLeft();
  //TurnRight();
  //UTurnLeft();
  //UTurnRight();
  //TracJC();
  //TracJCBack();
  //Finish();
  
 }

void loop() {
  // put your main code here, to run repeatedly:
  MoveTheCanJuniorMode();
  Finish();
}
void ShowRobotMode()
{
  oled.text(6,0,"3:Move The Can Junior ");  
  FontSensorNumber = 2; BackSensorNumber = 2;
  PidStatus=0;    //0:กรณีโค้งน้อยๆ 1:กรณีโค้งเยอะๆ
}
void CheckKnobMode()  //เช็คดูว่ามีการปรับค่า knob เพื่อเปลี่ยนโหมดหรือไม่
{
  int Num;
  Num = abs(knob()-KnobBase);
  if((Num>1000)) //ปรับค่าโหมดจาก knob
  {
    sound(10000,200);
    Num = abs(knob()-KnobBase);
    if((Num>1000)) //ปรับค่าโหมดจาก knob
    {
      RobotMode = (RobotMode+1)%6;
      ShowRobotMode();        
      oled.show();               //แสดงบนหน้าจอ
      KnobBase=knob();
    }
  }
}

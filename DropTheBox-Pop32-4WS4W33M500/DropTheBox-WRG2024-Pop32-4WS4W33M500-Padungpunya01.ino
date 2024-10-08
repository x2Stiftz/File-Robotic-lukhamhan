#include <POP32.h>

int Speed, SlowSpeed, ACCSpeed, BaseSpeed, LeftBaseSpeed, RightBaseSpeed, TurnSpeed, MaxSpeed, SonarSpeed, DistanceRef;
int Error, PreError, Kp, Kd, Ki, Kt, BackLeftBaseSpeed, BackRightBaseSpeed;
int RefL2, RefL1,  RefR1, RefR2, SumError;
int L2, L1, R1, R2;
long Timer, Timer2, Timer3;
int SW_OK_Status, Error99Check = 0, digital_sw = 0;
int KnobBase;
int CanStatus = 0;

#define No 0
#define Yes 1

#define Mode0 0
#define Mode1 1
#define Mode2 2
#define Mode3 3
#define Mode4 4

#define WheelDrive  1   //0:ขับเคลื่อน 2 ล้อ , 1:ขับเคลื่อน 4 ล้อ
#define SwitchTime  200 //เวลาในการตรวจสอบการกดสวิชในหน่วย ms

int Mode = Mode0;

int PidStatus = 0;  //0:กรณีโค้งน้อยๆ 1:กรณีโค้งเยอะๆ
int ErrorClear = 0; //0:เคลียร์ Error , 1:ไม่ต้องเคลียร์

int TuneBoxMode = 1;     //0:ไม่จูนก่อนปล่อยบล๊อค 1:จูนก่อนปล่อยบล๊อค
int KpChange=0,KdChange=0;

void setup() {

  DistanceRef = 3;     //0:ไม่เช็คสิ่งกีดขวาง ,>0 เช็คสิ่งกีดขวาง
  Speed = 60;
  ACCSpeed = 60;
  SlowSpeed = 50;
  BaseSpeed = Speed;
  TurnSpeed = Speed;
  SonarSpeed = 60;
  InitialSpeed();
  InitialRef();
  beep(0);
  oled.clear();                 //เคลียร์หน้าจอ
  oled.mode(0);                 //หมุนหน้าจอ 0 องศา
  oled.textSize(1);             //กำหนดขนาดตัวอักษร
  oled.text(0, 0, "  Ubon TP Robotics"); //กำหนดข้อความที่จะแสดง
  oled.text(1, 0, "   Drop The Box   ");
  oled.text(2, 0, "    Padungpunya   ");
  oled.text(3, 0, "     Speed = %d   ", Speed);
  oled.text(4, 0, "     ACCSpeed=%d", ACCSpeed);
  oled.text(5, 0, "     OK to Start ");
  //ShowRobotMode();    //แสดงโหมดที่เลือกไว้
  oled.show();                  //แสดงบนหน้าจอ
  SW_OK_Status = No;
  KnobBase = knob();
  while (SW_OK_Status == No)  { // waiting "OK" button
    if (Read_sw_OK()) {
      StartTimer();
      Mode = Mode0;
      SW_OK_Status = Yes;
      beep(1);
      while (Read_sw_OK())  { //wait unpress OK button
        if (ReadTimer() >= 2000) {
          beep(2);
          delay(100);
          ServoGripDown();
          ServoGrip();
          Kick(1,1,1,400);
          delay(1000);
          ServoGripUp();
          ServoPut();
          Show4Analog();
          SW_OK_Status = No;
        }
      }
    }
    //else CheckKnobMode();  //เช็คดูว่ามีการปรับค่า knob เพื่อเปลี่ยนโหมดหรือไม่
    if (SW_A())
    {
      StartTimer();
      beep(1);
      while (SW_A())  {} //wait unpress SW A button
      if (ReadTimer() >= SwitchTime) Mode = Mode1;
      else  Mode = Mode2;
      SW_OK_Status = Yes;

    }
    if (SW_B())
    {
      StartTimer();
      beep(1);
      while (SW_B())  {} //wait unpress SW A button
      if (ReadTimer() >= SwitchTime) Mode = Mode3;
      else  Mode = Mode4;
      SW_OK_Status = Yes;
    }
  }
  BaseSpeed = Speed;
  oled.clear();
  oled.textSize(2);
  oled.text(0, 0, "  Starting   ");
  oled.text(1, 0, "  Mode=%d   ", Mode);
  oled.show();
  StartTimer2();
  SelectSpeed();

  //ForwardSpeedTime(BaseSpeed,1500);     //เดินหน้า
  //BackwardSpeedTime(BaseSpeed,1500);    //ถอยหลัง
  //TurnLeft();                           //เลี้ยวซ้าย
  //TurnRight();                          //เลี้ยวขวา
  //UTurnLeft();                          //กลับตัวด้านซ้าย
  //UTurnRight();                         //กลับตัวด้านขวา
  //Left(70,200);                         //เลี้ยวซ้ายแบบหน่วงเวลา
  //Right(70,200);                        //เลี้ยวขวาแบบหน่วงเวลา
  //TracJCStop();                         //เดินเช็ค 1 แยก เจอแยกหยุดทันที
  //TracJC();                             //เดินเช็ค 1 แยก เจอแยกเพื่อเตรียมเลี้ยว
  //TracJCSpeed();                        //เดินเช็ค 1 แยก เจอแยกเพื่อเตรียมตรงไป
  //TracJCL();
  //TracJCR();
  //TracJCRLorR();
  //TracJCStopBack();                     //เดินถอยหลังเช็ค 1 แยก เจอแยกหยุดทันที
  //TracJCBack();                         //เดินถอยหลังเช็ค 1 แยก เจอแยกเพื่อเตรียมเลี้ยว
  //TracJCSpeedBack();                    //เดินถอยหลังเช็ค 1 แยก เจอแยกเพื่อเตรียมถอยตรงไป
  //TracSonar();                          //เดินตามเส้นเช็ควัตถุใช้ infrared
  //TracSpeedTime(Speed,500);             //เดินตามเส้นแบบหน่วงเวลา
  //TracSpeedTimeBack(Speed,500);         //เดินถอยหลังตามเส้นแบบหน่วงเวลา
  //TracJCSpeedTime(Speed,20);            //เดินตามเส้นเช็คแยกแบบกำหนดความเร็วการเดินและเวลาในการเดินข้ามแยก
  //TracJCSpeedTimeBack(Speed,20);        //เดินถอยหลังตามเส้นเช็คแยกแบบกำหนดความเร็วการเดินและเวลาในการเดินข้ามแยก
  //CurveLeft(70,80);                     //โค้งอ้อมด้านซ้าย
  //CurveRight(70,80);                    //โค้งอ้อมด้านขวา
  //Grip();                               //คีบกระป๋อง
  //Put();                                //วางกระป๋อง
  //GripUp();                             //ยกแขนขึ้น
  //GripDown();                           //ยกแขนลง
  //Kick(1,1,1,400);  //0:ไม่ปล่อย 1:ปล่อย (L,C,R,Time)
  //Finish();   //จบการทำงาน

}
void loop() {
  // put your main code here, to run repeatedly:
  Box1();   //1
  Box2();   //2
  Box3();
  Finish();
}
void ShowRobotMode()
{
  switch (TuneBoxMode)
  {
    case 0 : oled.text(6, 0, " 0:Normal Mode ");  //0:ก่อนปล่อยลูกบาศก์ไม่ต้องจูน
      break;
    case 1 : oled.text(6, 0, " 1:Tune Mode ");    //1:จูนก่อนปล่อยลูกบาศก์
      break;
  }
}
void CheckKnobMode()  //เช็คดูว่ามีการปรับค่า knob เพื่อเปลี่ยนโหมดหรือไม่
{
  int Num;
  Num = abs(knob() - KnobBase);
  if ((Num > 1000)) //ปรับค่าโหมดจาก knob
  {
    sound(10000, 200);
    Num = abs(knob() - KnobBase);
    if ((Num > 1000)) //ปรับค่าโหมดจาก knob
    {
      TuneBoxMode = (TuneBoxMode + 1) % 2;
      ShowRobotMode();
      oled.show();               //แสดงบนหน้าจอ
      KnobBase = knob();
    }
  }
}

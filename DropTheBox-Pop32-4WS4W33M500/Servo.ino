void ServoGrip()
{
  servo(1,55);
}
void ServoPut0()
{
  servo(1,110);
}
void ServoPut()
{
  servo(1,160);
}
void ServoGripUp()
{
  servo(2,35);
}
void ServoGripDown()
{
  servo(2,140);
}
void Grip()
{
  OffMotor();
  ServoGrip();
  delay(300); 
}
void Put()
{
  OffMotor();
  ServoPut();
  delay(300);   
}
void GripUp()
{
  OffMotor(); 
  ServoGripUp();
  delay(300);
}
void GripDown()
{
  OffMotor(); 
  ServoGripDown();
  delay(300);
}
/**********************ปล่อยลูกบาศก์**********************************/
void ServoKickL()
{
  servo(3,100);
}
void ServoKickC()
{
  servo(4,100);
}
void ServoKickR()
{
  servo(5,100);
}
void ServoCloseL()
{
  servo(3,180);
}
void ServoCloseC()
{
  servo(4,180);
}
void ServoCloseR()
{
  servo(5,170);
}
void Kick(int L,int C, int R, int Time)  //0:ไม่ปล่อย 1:ปล่อย
{
  MotorStop();
  if(L==1) ServoKickL();
  if(C==1) ServoKickC();
  if(R==1) ServoKickR();
  delay(Time);
  if(L==1) ServoCloseL();
  if(C==1) ServoCloseC();
  if(R==1) ServoCloseR();
}

void ServoGrip()
{
  servo(1,40);
}
void ServoPut0()
{
  servo(1,85);
}
void ServoPut()
{
  servo(1,130);
}
void ServoGripUp()
{
  servo(2,30);
}
void ServoGripDown()
{
  servo(2,145);
}
void Grip()
{
  OffMotor();
  ServoGrip();
  delay(50);
}
void Put()
{
  OffMotor();
  delay(100); 
  ServoPut();
  delay(50);
}
void GripUp()
{
  OffMotor(); 
  ServoGripUp();
  delay(100);
}
void GripDown()
{
  OffMotor(); 
  ServoGripDown();
  delay(100);
}

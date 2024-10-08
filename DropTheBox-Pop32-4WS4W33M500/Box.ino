#define KPTemp -9
void Box1()
{
  KpChange=KPTemp;
  ForwardSpeedTime(Speed,100);
  TracJCSpeed();
  TracJCStop();
  Kick(1,1,1,400);  
  BackwardSpeedTime(60,480);
  TurnLeft();
}
void Box2()
{
  KpChange=0;
  TracJC();
  ForwardSpeedTime(60,40);
  Right(70,220);
  Kick(1,1,1,400);
  BackwardSpeedTime(60,60);
  TurnLeft();
}
void Box3()
{
  KpChange=KPTemp;
  BackwardSpeedTime(60,480);
  TurnRight();
  TracJCSpeed();
  TracJCStop();
  Kick(1,1,1,400);
  BackwardSpeedTime(60,480);
  TurnRight();
}

void MoveTheCanJuniorMode()  
{ 
  for(int i=0; i<1; i++)
  {
    AtoB();
  }       
}
void AtoB()
{
  TracSpeedTime(SlowSpeed,100);
  TracSpeedTime(BaseSpeed,27000/BaseSpeed);
  ServoPut0();
  TracJCSlowStop();
  Grip();                 //Can A
  TracSpeedTimeBack(BaseSpeed,25000/BaseSpeed);
  TracJCBack();
  TurnRight2Sensor();
  TracSpeedTime(SlowSpeed,100);
  TracSpeedTime(BaseSpeed,27000/BaseSpeed);
  TracJCSlowStop();
  ForwardSpeedTime(SlowSpeed,10);
  Put();
}

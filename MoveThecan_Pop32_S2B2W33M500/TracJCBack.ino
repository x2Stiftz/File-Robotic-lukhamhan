void TracJCStopBack() 
{  
  InitialSpeed();
  //TracSpeedTimeBack(BaseSpeed,5000/BaseSpeed);
  CalErrorBack();
  while(Error<100)
  {
      TracPIDBack();
      StartTimer();
      while((ReadTimer()<KtB)&&(Error<100))
      {
        CalErrorBack();           
      }
  }
}
void TracJCBack() 
{
  TracJCStopBack();
  Backward();
  if(BaseSpeed<=50) delay(7000/BaseSpeed);
  else if(BaseSpeed<=60) delay(5800/BaseSpeed); 
  else if(BaseSpeed<=70) delay(3300/BaseSpeed);
  else if(BaseSpeed<=80) delay(2000/BaseSpeed);
  else if(BaseSpeed<=90) delay(1500/BaseSpeed);
  else delay(800/BaseSpeed);
}
void TracSpeedTimeBack(int TracSpeed, int TracTime) {
  int TempSpeed=BaseSpeed;
  BaseSpeed = TracSpeed;
  InitialSpeed();
  StartTimer();
  CalErrorBack();
  while(ReadTimer()<TracTime)
  {
    TracPIDBack();
    delay(Kt);
    CalErrorBack();
  }
  BaseSpeed = TempSpeed;
  InitialSpeed();
}
void TracJCSpeedTimeBack(int MotorSpeed, int TimeDelay) {
  BaseSpeed = MotorSpeed;
  TracJCStopBack();
  Backward();
  delay(TimeDelay);
  BaseSpeed = Speed;
  InitialSpeed();
}
void TracJCSpeedBack() 
{
  BaseSpeed = ACCSpeed;
  TracJCStopBack();
  Backward();
  delay(1000/BaseSpeed);
  while(Error>=100)
  {
    CalError();
  }
  delay(5000/BaseSpeed);
  BaseSpeed = Speed;
  InitialSpeed();
}

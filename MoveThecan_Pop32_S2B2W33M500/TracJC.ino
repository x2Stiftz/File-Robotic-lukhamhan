void TracJCStop() 
{  
  InitialSpeed();
  //TracSpeedTime(BaseSpeed,5000/BaseSpeed);
  CalError();
  while(Error<99)
  {
    TracPID();
    StartTimer();
    while((ReadTimer()<Kt)&&(Error<99))
    {
      CalError();
    }
  }
}
void TracJC() 
{
  TracJCStop();
  TuneJC();
}
void TuneJC()
{
  Forward();
  if(BaseSpeed<=50) delay(4000/BaseSpeed);
  else if(BaseSpeed<=60) delay(3000/BaseSpeed); 
  else if(BaseSpeed<=70) delay(1500/BaseSpeed);
  else if(BaseSpeed<=80) delay(500/BaseSpeed);
  //else if(BaseSpeed<=90) delay(500/BaseSpeed);
}
void TracJCStraight() 
{
  TracJC();
  ForwardDelay(5000/BaseSpeed);
}
void TracJCSlowStop() 
{
  BaseSpeed = SlowSpeed;
  TracJCStop();
  BaseSpeed = Speed;
  InitialSpeed();
}
void TracJCSlow() {
  TracJCSlowStop();
  Forward();
  while(Error>=100)
  {
    CalError();
  }
}
void TracJCSpeedTime(int MotorSpeed, int TimeDelay) {
  BaseSpeed = MotorSpeed;
  TracJCStop();
  Forward();
  delay(TimeDelay);
  BaseSpeed = Speed;
  InitialSpeed();
}
void TracJCSpeed() 
{
  BaseSpeed = ACCSpeed;
  TracJCStop();
  Forward();
  delay(1000/BaseSpeed);
  while(Error>=100)
  {
    CalError();
  }
  delay(2000/BaseSpeed);
  BaseSpeed = Speed;
  InitialSpeed();
}
void TracSpeedTime(int TracSpeed, int TracTime) {
  int TempSpeed=BaseSpeed;
  BaseSpeed = TracSpeed;
  InitialSpeed();
  StartTimer();
  CalError();
  while(ReadTimer()<TracTime)
  {
    TracPID();
    delay(Kt);
    CalError();
  }
  BaseSpeed = TempSpeed;
  InitialSpeed();
}

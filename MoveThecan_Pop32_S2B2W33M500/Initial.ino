void InitialRef() {
  RefL1 = 1413;     
  RefR1 = 2118;     
  RefBL1 = 1908;  
  RefBR1 = 1768;  
}
void InitialSpeed() 
{
  MaxSpeed = BaseSpeed;
  //MaxSpeed = 100;
  Ki = 0;
  Error = 0;
  PreError = 0;
  KiB = 0;
  if(BaseSpeed<=50)
  {
    LeftBaseSpeed = BaseSpeed-0;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp = 15;       //forward PID
    Kd = 160;
    Kt = 10;
    KpB = 15;       //Backward PID
    KdB = 160;
    KtB = 10;
  }
  else if(BaseSpeed<=60)
  {
    LeftBaseSpeed = BaseSpeed-0;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp = 17;       //forward PID
    Kd = 160;
    Kt = 10;
    KpB = 17;       //Backward PID
    KdB = 160;
    KtB = 10;
  }
  else if(BaseSpeed<=70)
  {
    LeftBaseSpeed = BaseSpeed-0;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp = 19;       //forward PID
    Kd = 160;
    Kt = 10;
    KpB = 19;       //Backward PID
    KdB = 160;
    KtB = 10;
  }
  else if(BaseSpeed<=80)
  {
    LeftBaseSpeed = BaseSpeed-0;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp = 21;       //forward PID
    Kd = 160;
    Kt = 10;
    KpB = 21;       //Backward PID
    KdB = 160;
    KtB = 10;
  }
  else if(BaseSpeed<=90)
  {
    LeftBaseSpeed = BaseSpeed-0;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp = 23;       //forward PID
    Kd = 160;
    Kt = 10;
    KpB = 23;       //Backward PID
    KdB = 160;
    KtB = 10;
  }
  else
  {
    LeftBaseSpeed = BaseSpeed-0;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp =25;       //forward PID
    Kd = 160;
    Kt = 10;
    KpB = 25;       //Backward PID
    KdB = 160;
    KtB = 10;
  }
}  

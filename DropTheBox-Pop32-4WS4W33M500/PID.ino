void CalError()
{
  CalError4Sensor(); 
}
void ConvertADC()
{
  Read4Analog(); 
  if(L2<RefL2) L2 = 0;else L2 = 1;  //0:ดำ 1:ขาว
  if(L1<RefL1) L1 = 0;else L1 = 1;
  if(R1<RefR1) R1 = 0;else R1 = 1;
  if(R2<RefR2) R2 = 0;else R2 = 1;
}
void CalError4Sensor() {
  ConvertADC();
  if((L2==1)&&(L1==1)&&(R1==1)&&(R2==0)) Error = 3; 
  else if((L2==1)&&(L1==1)&&(R1==0)&&(R2==0)) Error = 2; 
  else if((L2==1)&&(L1==1)&&(R1==0)&&(R2==1)) Error = 1; 
  else if((L2==1)&&(L1==1)&&(R1==1)&&(R2==1)) Error = 0; 
  else if((L2==1)&&(L1==0)&&(R1==1)&&(R2==1)) Error = -1; 
  else if((L2==0)&&(L1==0)&&(R1==1)&&(R2==1)) Error = -2; 
  else if((L2==0)&&(L1==1)&&(R1==1)&&(R2==1)) Error = -3; 
  else if((L2==0)&&(L1==0)&&(R1==0)&&(R2==0)) Error = 100; 
  else if((L2==0)&&(L1==0)&&(R1==0)) Error = 101; 
  else if((L1==0)&&(R1==0)&&(R2==0)) Error = 102; 
}

void TracPID()  {
  int Output, LeftSpeed, RightSpeed, KpTemp;
  if(abs(Error)<0) KpTemp=1; else KpTemp=Kp;
  Output = (KpTemp*Error) + (Ki*SumError) + (Kd*(Error-PreError));
  LeftSpeed = LeftBaseSpeed + Output;
  RightSpeed = RightBaseSpeed - Output;
  if(LeftSpeed>MaxSpeed) LeftSpeed = MaxSpeed;
  else 
  {
    if(PidStatus!=0) {if(LeftSpeed<-MaxSpeed) LeftSpeed = -MaxSpeed;}
    else if(LeftSpeed<0) LeftSpeed = 0;//new pid
  }
  if(RightSpeed>MaxSpeed) RightSpeed = MaxSpeed;
  else 
  {
    if(PidStatus!=0) {if(RightSpeed<-MaxSpeed) RightSpeed = -MaxSpeed;}
    else if(RightSpeed<0) RightSpeed = 0;//new pid
  }
  if(WheelDrive==0)
  {
    motor(1,LeftSpeed); 
    motor(2,RightSpeed);
  }
  else
  {
    motor(1,LeftSpeed);
    motor(2,LeftSpeed); 
    motor(3,RightSpeed);
    motor(4,RightSpeed);
  }
  PreError = Error;
  SumError += Error;
}

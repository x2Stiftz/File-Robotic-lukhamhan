void CalError()
{
  CalError2Sensor(); 
}
void ConvertADC()
{
  Read2Analog();  
  if(L1<RefL1) L1 = 0;else L1 = 1;  //0:ดำ 1:ขาว
  if(R1<RefR1) R1 = 0;else R1 = 1;
}
void CalError2Sensor() {
  ConvertADC();
  if((L1==1)&&(R1==0)) Error = 1; 
  else if((L1==1)&&(R1==1)) Error = 0; 
  else if((L1==0)&&(R1==1)) Error = -1;
  else if((L1==0)&&(R1==0)) Error = 100;
}
void TracPID()  {
  int Output, LeftSpeed, RightSpeed;
  Output = (Kp*Error) + (Ki*SumError) + (Kd*(Error-PreError));
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
void CalErrorBack()
{
  CalErrorBack2Sensor(); 
}
void ConvertADCBack()
{
  Read2AnalogBack();
  if(BL1<RefBL1) BL1 = 0; else BL1 = 1;    //0:ดำ 1:ขาว
  if(BR1<RefBR1) BR1 = 0; else BR1 = 1;
}
void CalErrorBack2Sensor() {
  ConvertADCBack();
  if((BL1==1)&&(BR1==0)) Error = 1; 
  else if((BL1==1)&&(BR1==1)) Error = 0; 
  else if((BL1==0)&&(BR1==1)) Error = -1;
  else if((BL1==0)&&(BR1==0)) Error = 100; 
}
void TracPIDBack()  {
  int Output, LeftSpeed, RightSpeed;
  Output = (KpB*Error) + (KiB*SumError) + (KdB*(Error-PreError));
  LeftSpeed = BackLeftBaseSpeed + Output;
  RightSpeed = BackRightBaseSpeed - Output;
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
    motor(1,-LeftSpeed); 
    motor(2,-RightSpeed);
  }
  else
  {
    motor(1,-LeftSpeed);
    motor(2,-LeftSpeed); 
    motor(3,-RightSpeed);
    motor(4,-RightSpeed);
  }
  PreError = Error;
  SumError += Error;
}

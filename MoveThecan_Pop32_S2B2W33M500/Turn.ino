#define BrakeSpeed 100
#define BrakeTime 10
void TurnLeft2Sensor() {
    MotorStop();
    if(WheelDrive==0) sl(TurnSpeed);
    else SL(TurnSpeed);
    delay(6000/TurnSpeed);
    if(TurnSpeed>=70)
    {
      if(WheelDrive==0) sl(50);
      else SL(50);
    }
    ConvertADC();
    while((L1==1)) {ConvertADC();}
    if(BrakeTime>0) Right(BrakeSpeed,BrakeTime);
    else MotorStop();
}
void TurnRight2Sensor() {
    MotorStop();
    if(WheelDrive==0) sr(TurnSpeed);
    else SR(TurnSpeed);
    delay(6000/TurnSpeed);
    if(TurnSpeed>=70)
    {
      if(WheelDrive==0) sr(50);
      else SR(50);
    }
    ConvertADC();
    while((R1==1)) {ConvertADC();}
    if(BrakeTime>0) Left(BrakeSpeed,BrakeTime);
    else MotorStop();
}
void UTurnLeft2Sensor() {
    MotorStop();
    if(WheelDrive==0) sl(TurnSpeed);
    else SL(TurnSpeed);
    delay(12000/TurnSpeed);
    if(TurnSpeed>=60)
    {
      if(WheelDrive==0) sl(50);
      else SL(50);
    }
    ConvertADC();
    while((L1==1)) {ConvertADC();}
    if(BrakeTime>0) Right(BrakeSpeed,BrakeTime);
    else MotorStop();
}
void UTurnRight2Sensor() {
    MotorStop();
    if(WheelDrive==0) sr(TurnSpeed);
    else SR(TurnSpeed);
    delay(12000/TurnSpeed);
    if(TurnSpeed>=60)
    {
      if(WheelDrive==0) sr(50);
      else SR(50);
    }
    ConvertADC();
    while((R1==1)) {ConvertADC();}
    if(BrakeTime>0) Left(BrakeSpeed,BrakeTime);
    else MotorStop();
}
void Left(int Speed , int Time){
  MotorStop();
  if(WheelDrive==0) sl(Speed);
  else SL(Speed);
  delay(Time);
  MotorStop();
}
void Right(int Speed , int Time){
  MotorStop();
  if(WheelDrive==0) sr(Speed);
  else SR(Speed);
  delay(Time);
  MotorStop();
}

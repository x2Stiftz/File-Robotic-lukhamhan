void Read4Analog() {
  L2 = analog(0);
  L1 = analog(1);
  R1 = analog(2);
  R2 = analog(3);
}
int Sonar()
{
  int Sonar;
   
  //Sonar = (analog(8)/40); //ZX-sonar
  Sonar = analog(8);   //infrared
  Sonar -= 1150; 
  if(Sonar<=0) Sonar = 1;
  Sonar = 6000/Sonar;
  return(Sonar);
}

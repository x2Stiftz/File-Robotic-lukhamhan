void Read2Analog() {
  L1 = analog(0);
  R1 = analog(1);
}
void Read2AnalogBack() {
  BL1 = analog(2);  
  BR1 = analog(3);
}
int Sonar()
{
  int Sonar;
   
  //Sonar = (analog(7)/40); //ZX-sonar
  Sonar = analog(8);   //infrared
  Sonar -= 1150; 
  if(Sonar<=0) Sonar = 1;
  Sonar = 6000/Sonar;
  return(Sonar);
}
